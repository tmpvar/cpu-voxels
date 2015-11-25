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
  } bounding_tree_node_t;

  bounding_tree_node bounding_tree_create_node() {
    bounding_tree_node node = malloc(sizeof(bounding_tree_node_t));
    memset(node->children, NULL, sizeof(bounding_tree_node_t) * 8);
    node->brick = NULL;
    return node;
  }

  int bounding_tree_node_is_leaf(const bounding_tree_node node) {
    return node->brick != NULL;
  }

  // packs the position into a bitmask that can be used to directly lookup
  // the appropriate node
  int bounding_tree_octant_from_vec3(bounding_tree_node node, vec3 pos) {
    vec3 diff = node->center - pos;
    return  (diff[0] > 0 ? 1 : 0) | (diff[1] > 0 ? 2 : 0) | (diff[2] > 0 ? 4 : 0);
  }

  typedef struct voxel_scene_t {
    bounding_tree_node root;
  } *voxel_scene, voxel_scene_t;

  voxel_scene voxel_scene_create() {
    voxel_scene scene = (voxel_scene)malloc(sizeof(voxel_scene_t));
    scene->root = bounding_tree_create_node();

    scene->root->bounds[0] = vec3f(0.0f);
    scene->root->bounds[1] = vec3f(0.0f);
    scene->root->center = vec3f(0.0f);

    return scene;
  }

  void voxel_scene_add_brick(voxel_scene scene, voxel_brick brick) {
    // walk the tree and find the slot in which the
    // brick should live
    bounding_tree_node node = scene->root;
    int octant;
    while (1) {
      octant = bounding_tree_octant_from_vec3(node, brick->center);

      if (node->children[octant] == NULL) {
        break;
      }
      node = node->children[octant];
      
      // update bounding box on the way down
      
    }
    
    // TODO: 
    
    // split the node
    node->children[octant] = bounding_tree_create_node();
    node->children[octant]->brick = brick;
    
    printf("made it here! %i\n", bounding_tree_octant_from_vec3(node, brick->center));

  }

  void voxel_scene_ray(voxel_scene scene, ray3 *r) {

  }

#endif
