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

  bounding_tree_node bounding_tree_create_node(const float radius) {
    bounding_tree_node node = malloc(sizeof(bounding_tree_node_t));
    memset(node->children, 0, sizeof(bounding_tree_node) * 8);
    node->brick = NULL;
    node->radius = radius;
    node->bounds[0] = vec3f(-radius);
    node->bounds[1] = vec3f(radius);
    return node;
  }

  int bounding_tree_node_is_leaf(const bounding_tree_node node) {
    return node->brick != NULL;
  }

  // packs the position into a bitmask that can be used to directly lookup
  // the appropriate node
  int bounding_tree_octant_from_vec3(bounding_tree_node node, vec3 pos) {
    vec3 diff = pos - node->center;
    return  (diff[0] > 0 ? 1 : 0) | (diff[1] > 0 ? 2 : 0) | (diff[2] > 0 ? 4 : 0);
  }

  vec3 bounding_tree_corner_from_octant(bounding_tree_node node, const int octant) {
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
    scene->root = bounding_tree_create_node(VOXEL_BRICK_SIZE);

    scene->root->center = vec3f(0.0f);
    scene->root->level = 0;

    return scene;
  }

  void voxel_scene_add_brick(voxel_scene scene, voxel_brick brick) {
    bounding_tree_node new_root;
    float root_radius;
    int octant;


    // if the incoming brick is out of bounds of the current octree,
    // then re-root as many times as necessary to bound the brick.
    while (!aabb_contains(scene->root->bounds, brick->center)) {
      root_radius = scene->root->radius * 2.0f;
      new_root = bounding_tree_create_node(root_radius);

      // move the current root under the new root
      octant = bounding_tree_octant_from_vec3(new_root, scene->root->center);
      new_root->center = bounding_tree_corner_from_octant(scene->root, octant);
      new_root->children[octant] = scene->root;

      // replace the scene root with the new root
      scene->root = new_root;
    }

    // walk the tree and find the slot in which the brick should live
    bounding_tree_node node = scene->root;

    while (1) {
      octant = bounding_tree_octant_from_vec3(node, brick->center);

      if (node->children[octant] == NULL) {
        break;
      }
      node = node->children[octant];
    }

    // split the node
    node->children[octant] = bounding_tree_create_node(VOXEL_BRICK_HALF_SIZE);
    node->children[octant]->brick = brick;
  }

  int voxel_scene_ray(voxel_scene scene, ray3 *r) {
    float t;
    if (ray_isect(r, scene->root->bounds, &t)) {
      vec3 isect = r->origin + r->dir * vec3f(t);
      int octant = bounding_tree_octant_from_vec3(scene->root, isect);

      // TODO: handle the cases where the ray misses:
      // - voxels in brick
      // - empty octant

      bounding_tree_node node = scene->root;
      while (1) {
        if (node->brick != NULL) {
          int trace[3];
          if (voxel_brick_traverse(node->brick, isect, r->dir, 0, trace)) {
            return 1;
          } else {
            return 0;
          }
        } else if (node->children[octant] == NULL) {
          return 0;
        } else {
          node = node->children[octant];
        }
      }
    }
    return 0;
  }

#endif
