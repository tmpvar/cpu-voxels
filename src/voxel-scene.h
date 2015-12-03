#ifndef __SCENE__
#define __SCENE__

  #include <string.h>
  #include "voxel.h"
  #include "aabb.h"
  #include "vec.h"

  typedef struct bounding_tree_node_t *bounding_tree_node;

  struct bounding_tree_node_t {
    bounding_tree_node children[8];
    aabb bounds;
    vec3 center;
    voxel_brick brick;
    unsigned int level;
    float radius;
  } bounding_tree_node_t;

  bounding_tree_node bounding_tree_create_node(const float radius, const vec3 center) {
    bounding_tree_node node = (bounding_tree_node)malloc(sizeof(bounding_tree_node_t));
    memset(node->children, 0, sizeof(bounding_tree_node) * 8);
    node->brick = NULL;
    node->radius = radius;
    node->center = center;
    vec3 r = vec3f(radius);
    node->bounds[0] = center - r;
    node->bounds[1] = center + r;
    return node;
  }

  static inline int bounding_tree_node_is_leaf(const bounding_tree_node node) {
    return node->brick != NULL;
  }

  // packs the position into a bitmask that can be used to directly lookup
  // the appropriate node
  static inline int bounding_tree_octant_from_vec3(const bounding_tree_node node, const vec3 pos) {
    return  (pos[0] > node->center[0] ? 1 : 0) | (pos[1] > node->center[1] ? 2 : 0) | (pos[2] > node->center[2] ? 4 : 0);
  }

  static inline vec3 bounding_tree_corner_from_octant(bounding_tree_node node, const int octant) {
    return vec3_create(
      octant & 1 ? node->radius : -node->radius,
      octant & 2 ? node->radius : -node->radius,
      octant & 4 ? node->radius : -node->radius
    );
  }

  static int bounding_tree_ray(bounding_tree_node node, ray3 *r, int accumulator[3]) {
    vec3 isect;
    int closest = -1;
    float dist = FLT_MAX;

    if (!ray_isect_simd(r, node->bounds, &isect)) {
      return closest;
    }

    if (accumulator[0] < 255) {
      accumulator[0] += 10;
      accumulator[1] += 10;
      accumulator[2] += 10;
    }

    if (node->brick != NULL) {
      for (int v=0; v<8; v++) {
        vec3 corner = node->center + bounding_tree_corner_from_octant(node, v);
        aabb bounds;
        bounds[0] = _mm_min_ps(corner, node->center);
        bounds[1] = _mm_max_ps(corner, node->center);

        if (node->brick->voxels[v] > 0.0f && ray_isect_simd(r, bounds, &isect)) {
          float ldist = vec3_distance(isect, r->origin);
          if (ldist < dist) {
            closest = v;
            dist = ldist;
          }
        }
      }

      return closest;
    } else {
      // recurse into the structure on the appropriate node
      for (int i=0; i<8; i++) {
        if (node->children[i] != NULL) {
          int ret = bounding_tree_ray(node->children[i], r, accumulator);
          if (ret > -1) {
            float ldist = vec3_distance(node->children[i]->center, r->origin);
            if (ldist < dist) {
              closest = ret;
              dist = ldist;
            }
          }
        }
      }

      return closest;
    }

    return closest;
  }

  typedef struct voxel_scene_t {
    bounding_tree_node root;
  } *voxel_scene, voxel_scene_t;

  voxel_scene voxel_scene_create() {
    voxel_scene scene = (voxel_scene)malloc(sizeof(voxel_scene_t));
    scene->root = bounding_tree_create_node(VOXEL_BRICK_SIZE, vec3f(VOXEL_BRICK_SIZE));
    scene->root->level = 1;

    return scene;
  }

  void voxel_scene_expand_over_position(const voxel_scene scene, const vec3 pos) {
    int octant = -1;

    // if the incoming brick is out of bounds of the current octree,
    // then re-root as many times as necessary to bound the brick.
    while (!aabb_contains(scene->root->bounds, pos)) {

     // move the current root under the new root
     octant = bounding_tree_octant_from_vec3(scene->root, pos);

     float root_radius = scene->root->radius * 2.0f;
     bounding_tree_node new_root = bounding_tree_create_node(
       root_radius,
       scene->root->center + bounding_tree_corner_from_octant(scene->root, octant)
     );
     new_root->level = scene->root->level + 1;

     int newoctant = bounding_tree_octant_from_vec3(new_root, scene->root->center);
     new_root->children[newoctant] = scene->root;

     // replace the scene root with the new root
     scene->root = new_root;
    }
  }

  bounding_tree_node voxel_scene_node_for_position(const bounding_tree_node start, const vec3 pos) {
    int octant = -1;
    bounding_tree_node node = start;

    while (node->level) {
      // leaves are containers for bricks, utilize the previously computed octant
      octant = bounding_tree_octant_from_vec3(node, pos);

      if (node->children[octant] == NULL) {
        node->children[octant] = bounding_tree_create_node(
          node->radius * 0.5f,
          node->center + bounding_tree_corner_from_octant(node, octant) * vec3f(0.5f)
        );
        node->children[octant]->level = node->level - 1;
      }
      node = node->children[octant];
    }

    return node;
  }

  bounding_tree_node voxel_scene_add_brick(voxel_scene scene, voxel_brick brick) {

    // ensure the scene covers the new brick location
    voxel_scene_expand_over_position(scene, brick->center);

    // walk the tree and find the slot in which the brick should live
    bounding_tree_node node = voxel_scene_node_for_position(scene->root, brick->center);

    // setup the leaf
    node->brick = brick;
    node->bounds[0] = brick->bounds[0];
    node->bounds[1] = brick->bounds[1];
    node->center = brick->center;

    return node;
  }

  int voxel_scene_ray(voxel_scene scene, ray3 *r, int accumulator[3]) {
    return bounding_tree_ray(scene->root, r, accumulator);
  }

  void voxel_scene_set(const voxel_scene scene, const int x, const int y, const int z, const float v) {
    vec3 brick_half = vec3f(VOXEL_BRICK_HALF_SIZE);
    vec3 brick_corner = _mm_floor_ps(vec3_create((float)x, (float)y, (float)z)) * vec3f(VOXEL_SIZE);
    vec3 brick_pos = brick_corner + brick_half;

    voxel_scene_expand_over_position(scene, brick_pos);

    // walk the tree and find the slot in which the brick should live
    bounding_tree_node node = voxel_scene_node_for_position(scene->root, brick_pos);

    if (node->brick == NULL) {
      node->brick = voxel_brick_create();
      voxel_brick_fill_constant(node->brick, 0.0f);
    }

    voxel_brick_position(node->brick, brick_pos);
    voxel_brick_set(
      node->brick,
      x % VOXEL_BRICK_WIDTH,
      y % VOXEL_BRICK_WIDTH,
      z % VOXEL_BRICK_WIDTH,
      v
    );
  }

#endif
