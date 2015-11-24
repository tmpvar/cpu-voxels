#ifndef __VOXEL__
#define __VOXEL__
  #include <string.h>
  #include <math.h>
  #include <float.h>
  #include "vec.h"
  #include "aabb.h"

  #define VOXEL_BRICK_WIDTH 8
  #define VOXEL_BRICK_HALF_WIDTH VOXEL_BRICK_WIDTH/2
  #define VOXEL_BRICK_LENGTH VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH
  #define VOXEL_SIZE 1
  #define VOXEL_BRICK_HALF_SIZE VOXEL_BRICK_HALF_WIDTH * VOXEL_SIZE
  #define VOXEL_BRICK_SIZE VOXEL_BRICK_WIDTH * VOXEL_SIZE

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
    memset(brick->voxels, v, sizeof(brick->voxels));
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

  static inline float sign(const float a) {
    return a < 0 ? -1.0f : 1.0f;
  }

  static inline float mod(const float value, const float modulus) {
    return fmod(fmod(value, modulus) + modulus, modulus);
  }

  static inline float intbound(float s, float ds) {
    if (ds < 0) {
      s = -s;
      ds = -ds;
    }

    s = mod(s, 1);
    return (1-s)/ds;
  }

  // TODO: replace density with a callback?
  static inline int voxel_brick_traverse(
    voxel_brick *brick,
    const vec3 isect,
    const vec3 rd,
    const float density,
    int *out
  ) {

    float rdx = rd[0];
    float rdy = rd[1];
    float rdz = rd[2];

    float sx = sign(rdx);
    float sy = sign(rdy);
    float sz = sign(rdz);

    float x = isect[0] + rdx;
    float y = isect[1] + rdy;
    float z = isect[2] + rdz;

    float mx = intbound(x, rdx);
    float my = intbound(y, rdy);
    float mz = intbound(z, rdz);

    float dx = sx/rdx;
    float dy = sy/rdy;
    float dz = sz/rdz;
    int ix, iy, iz;

    while (
      x >= brick->bounds[0][0] &&
      y >= brick->bounds[0][1] &&
      z >= brick->bounds[0][2] &&
      x <= brick->bounds[1][0] &&
      y <= brick->bounds[1][1] &&
      z <= brick->bounds[1][2]
    ) {

      ix = floor(x);
      iy = floor(y);
      iz = floor(z);

      if (brick->voxels[ix][iy][iz] > density) {
        out[0] = ix;
        out[1] = iy;
        out[2] = iz;
        return 1;
      }

      if(mx < my) {
        if(mx < mz) {
          out[0] = -sx;
          out[1] = out[2] = 0;

          x += sx;
          mx += dx;
        } else {
          out[2] = -sz;
          out[0] = out[1] = 0;

          z += sz;
          mz += dz;
        }
      } else {
        if(my < mz) {
          out[1] = -sy;
          out[0] = out[2] = 0;

          y += sy;
          my += dy;
        } else {
          out[2] = -sz;
          out[0] = out[1] = 0;

          z += sz;
          mz += dz;
        }
      }
    }
    return 0;
  }
#endif
