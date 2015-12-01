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

  typedef struct voxel_scene_t {
    bounding_tree_node root;
  } *voxel_scene, voxel_scene_t;

  voxel_scene voxel_scene_create() {
    voxel_scene scene = (voxel_scene)malloc(sizeof(voxel_scene_t));
    scene->root = bounding_tree_create_node(VOXEL_BRICK_SIZE, vec3f(VOXEL_BRICK_SIZE));
    scene->root->level = 1;

    return scene;
  }

  void voxel_scene_expand_over_brick(const voxel_scene scene, const voxel_brick brick) {
    int octant = -1;

    // if the incoming brick is out of bounds of the current octree,
    // then re-root as many times as necessary to bound the brick.
    while (!aabb_contains(scene->root->bounds, brick->center)) {

     // move the current root under the new root
     octant = bounding_tree_octant_from_vec3(scene->root, brick->center);

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

  bounding_tree_node voxel_scene_add_brick(voxel_scene scene, voxel_brick brick) {
    int octant = -1;

    voxel_scene_expand_over_brick(scene, brick);

    // walk the tree and find the slot in which the brick should live
    bounding_tree_node node = scene->root;

    while (node->level) {
      // leaves are containers for bricks, utilize the previously computed octant
      octant = bounding_tree_octant_from_vec3(node, brick->center);

      if (node->children[octant] == NULL) {
        float node_radius = VOXEL_BRICK_HALF_SIZE * (float)(node->level);
        vec3 center = node->center + bounding_tree_corner_from_octant(node, octant) * vec3f(0.5f);
        node->children[octant] = bounding_tree_create_node(
          node_radius,
          center
        );
        node->children[octant]->level = node->level - 1;
      }
      node = node->children[octant];
    }

    // setup the leaf
    octant = bounding_tree_octant_from_vec3(node, brick->center);
    node->brick = brick;
    node->bounds[0] = brick->bounds[0];
    node->bounds[1] = brick->bounds[1];
    node->center = brick->center;

    return node;
  }

  static int bounding_tree_ray(bounding_tree_node node, ray3 *r, int accumulator[3]) {
    vec3 isect;

    if (accumulator[0] < 255) {
      accumulator[0] += 20;
      accumulator[1] += 20;
      accumulator[2] += 20;
    }

    if (ray_isect_simd(r, node->bounds, &isect)) {
      if (node->brick != NULL) {
        return voxel_brick_traverse(node->brick, isect, r->dir, 0);
      } else {
        // recurse into the structure on the appropriate node
        for (int i=0; i<8; i++) {
          if (node->children[i] != NULL) {
            int ret = bounding_tree_ray(node->children[i], r, accumulator);
            if (ret > -1) {
              return ret;
            }
          }
        }
      }
    }

    return -1;
  }

  int voxel_scene_ray(voxel_scene scene, ray3 *r, int accumulator[3]) {
    return bounding_tree_ray(scene->root, r, accumulator);
  }

#endif
