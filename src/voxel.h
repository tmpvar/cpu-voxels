#ifndef __VOXEL__
#define __VOXEL__
  #include <string.h>

  #include "vec.h"
  #include "aabb.h"

  #define VOXEL_BRICK_WIDTH 8
  #define VOXEL_BRICK_HALF_WIDTH VOXEL_BRICK_WIDTH/2
  #define VOXEL_BRICK_LENGTH VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH
  #define VOXEL_SIZE .1/VOXEL_BRICK_WIDTH
  #define VOXEL_BRICK_SIZE VOXEL_BRICK_HALF_WIDTH * VOXEL_SIZE

  typedef float (*set_callback_t)(const unsigned int x, const unsigned int y, const unsigned int z);

  typedef struct {
    float voxels[VOXEL_BRICK_WIDTH][VOXEL_BRICK_WIDTH][VOXEL_BRICK_WIDTH];
    vec3 center;
    aabb bounds;
    aabb_packet bounds_packet;
  } voxel_brick;

  void voxel_brick_set(voxel_brick *brick, const unsigned int x, const unsigned int y, const unsigned int z, float v) {
    brick->voxels[x][y][z] = v;
  }

  void voxel_brick_fill_constant(voxel_brick *brick, const float v) {
    memset(brick->voxels, v, sizeof(VOXEL_BRICK_LENGTH));
  }

  static void voxel_brick_fill(voxel_brick *brick, set_callback_t cb) {
    for (unsigned int x=0; x<VOXEL_BRICK_WIDTH; x++) {
      for (unsigned int y=0; y<VOXEL_BRICK_WIDTH; y++) {
        for (unsigned int z=0; z<VOXEL_BRICK_WIDTH; z++) {
          brick->voxels[x][y][z] = cb(x, y, z);
        }
      }
    }
  }

  static float voxel_brick_get(voxel_brick *brick, const unsigned int x, const unsigned int y, const unsigned int z) {
    return brick->voxels[x][y][z];
  }

  static void voxel_brick_position(voxel_brick *brick, const vec3 center) {
    // position the brick in space
    brick->center = center;

    // create a normal aabb
    vec3 corner = vec3f(VOXEL_SIZE * VOXEL_BRICK_HALF_WIDTH);
    brick->bounds[0] = _mm_sub_ps(center, corner);
    brick->bounds[1] = _mm_add_ps(center, corner);

    // create an aabb packet
    brick->bounds_packet[0] = _mm_set1_ps(brick->bounds[0][0]);
    brick->bounds_packet[1] = _mm_set1_ps(brick->bounds[0][1]);
    brick->bounds_packet[2] = _mm_set1_ps(brick->bounds[0][2]);
    brick->bounds_packet[3] = _mm_set1_ps(brick->bounds[1][0]);
    brick->bounds_packet[4] = _mm_set1_ps(brick->bounds[1][1]);
    brick->bounds_packet[5] = _mm_set1_ps(brick->bounds[1][2]);
  }


#endif
