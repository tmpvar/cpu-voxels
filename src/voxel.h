#ifndef __VOXEL__
#define __VOXEL__
  #include <string.h>

  #include "vec.h"

  #define BRICK_RADIUS 8
  #define BRICK_LENGTH BRICK_RADIUS*BRICK_RADIUS*BRICK_RADIUS
  #define VOXEL_SIZE 0.01f

  typedef float (*set_callback_t)(const unsigned int x, const unsigned int y, const unsigned int z);

  typedef struct {
    float voxels[BRICK_RADIUS][BRICK_RADIUS][BRICK_RADIUS];
    vec3 center;
  } voxel_brick;

  void voxel_brick_set(voxel_brick brick, const unsigned int x, const unsigned int y, const unsigned int z, float v) {
    brick.voxels[x][y][z] = v;
  }

  void voxel_brick_fill_constant(voxel_brick brick, const float v) {
    memset(brick.voxels, v, sizeof(BRICK_LENGTH));
  }

  static void voxel_brick_fill(voxel_brick brick, set_callback_t cb) {
    for (unsigned int x=0; x<BRICK_RADIUS; x++) {
      for (unsigned int y=0; y<BRICK_RADIUS; y++) {
        for (unsigned int z=0; z<BRICK_RADIUS; z++) {
          brick.voxels[x][y][z] = cb(x, y, z);
        }
      }
    }
  }

  static float voxel_brick_get(voxel_brick brick, const unsigned int x, const unsigned int y, const unsigned int z) {
    return brick.voxels[x][y][z];
  }

#endif
