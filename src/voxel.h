#ifndef __VOXEL__
#define __VOXEL__
  #include <string.h>
  #include <math.h>
  #include <float.h>
  #include "vec.h"
  #include "aabb.h"

  #define VOXEL_BRICK_WIDTH 128
  #define VOXEL_BRICK_HALF_WIDTH (VOXEL_BRICK_WIDTH/2.0f)
  #define VOXEL_SIZE 0.001f
  #define VOXEL_BRICK_HALF_SIZE (VOXEL_BRICK_HALF_WIDTH * VOXEL_SIZE)
  #define VOXEL_BRICK_SIZE (VOXEL_BRICK_WIDTH * VOXEL_SIZE)

  typedef float (*set_callback_t)(const unsigned int x, const unsigned int y, const unsigned int z);

  typedef struct {
    float *voxels;//[VOXEL_BRICK_WIDTH][VOXEL_BRICK_WIDTH][VOXEL_BRICK_WIDTH];
    vec3 center;
    aabb bounds;
    aabb_packet bounds_packet;
  } *voxel_brick, voxel_brick_t;

  static inline void voxel_brick_set(voxel_brick brick, const unsigned int x, const unsigned int y, const unsigned int z, float v) {
    brick->voxels[x*VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH + y*VOXEL_BRICK_WIDTH + z] = v;
  }

  voxel_brick voxel_brick_create() {
    voxel_brick out = (voxel_brick)malloc(sizeof(voxel_brick_t));
    // begin memory allocation
//    out->voxels = malloc(
    out->voxels = (float *)malloc(sizeof(float) * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH);


    //    out->voxels = (float *)malloc(sizeof(float) * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH);
    return out;
  }

  void voxel_brick_fill_constant(voxel_brick brick, const float v) {
    memset(brick->voxels, v, sizeof(float) * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH * VOXEL_BRICK_WIDTH);
  }

  static void voxel_brick_fill(voxel_brick brick, set_callback_t cb) {
    for (unsigned int x=0; x<VOXEL_BRICK_WIDTH; x++) {
      for (unsigned int y=0; y<VOXEL_BRICK_WIDTH; y++) {
        for (unsigned int z=0; z<VOXEL_BRICK_WIDTH; z++) {
          voxel_brick_set(brick, x, y, z, cb(x, y, z));
        }
      }
    }
  }

  static inline float voxel_brick_get(voxel_brick brick, const int x, const int y, const int z) {
    return brick->voxels[x*VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH + y*VOXEL_BRICK_WIDTH + z];
  }

  static void voxel_brick_position(voxel_brick brick, const vec3 center) {
    // position the brick in space
    brick->center = center;

    // create a normal aabb
    vec3 corner = vec3f(VOXEL_BRICK_HALF_SIZE);
    brick->bounds[0] = center - corner;
    brick->bounds[1] = center + corner;

    // create an aabb packet
    brick->bounds_packet[0] = _mm_set1_ps(brick->bounds[0][0]);
    brick->bounds_packet[1] = _mm_set1_ps(brick->bounds[0][1]);
    brick->bounds_packet[2] = _mm_set1_ps(brick->bounds[0][2]);
    brick->bounds_packet[3] = _mm_set1_ps(brick->bounds[1][0]);
    brick->bounds_packet[4] = _mm_set1_ps(brick->bounds[1][1]);
    brick->bounds_packet[5] = _mm_set1_ps(brick->bounds[1][2]);
  }

  static inline float sign(const float a) {
    return a < 0 ? -VOXEL_SIZE : VOXEL_SIZE;
  }

  static inline float mod(const float value, const float modulus) {
    return fmod(fmod(value, modulus) + modulus, modulus);
  }

  static inline float intbound(float s, float ds) {
    if (ds < 0) {
      s = -s;
      ds = -ds;
    }

    s = mod(s, VOXEL_SIZE);
    return (VOXEL_SIZE-s)/ds;
  }

  static int voxel_brick_traverse(
    voxel_brick brick,
    const vec3 isect,
    const vec3 rd,
    const float density,
    int *out
  ) {

    float rdx = rd[0] * VOXEL_SIZE;
    float rdy = rd[1] * VOXEL_SIZE;
    float rdz = rd[2] * VOXEL_SIZE;

    float sx = sign(rdx);
    float sy = sign(rdy);
    float sz = sign(rdz);

    float x = (isect[0] - brick->bounds[0][0]) + rdx;
    float y = (isect[1] - brick->bounds[0][1]) + rdy;
    float z = (isect[2] - brick->bounds[0][2]) + rdz;

    float mx = intbound(x, rdx);
    float my = intbound(y, rdy);
    float mz = intbound(z, rdz);

    float dx = sx/rdx;
    float dy = sy/rdy;
    float dz = sz/rdz;

    unsigned int ix = (int)floor(x / VOXEL_SIZE);
    unsigned int iy = (int)floor(y / VOXEL_SIZE);
    unsigned int iz = (int)floor(z / VOXEL_SIZE);

    int isx = (int)(sign(rdx) / VOXEL_SIZE);
    int isy = (int)(sign(rdy) / VOXEL_SIZE);
    int isz = (int)(sign(rdz) / VOXEL_SIZE);

    while (
      ix < VOXEL_BRICK_WIDTH &&
      iy < VOXEL_BRICK_WIDTH &&
      iz < VOXEL_BRICK_WIDTH
    ) {

      if (voxel_brick_get(brick, ix, iy, iz) > density) {
        out[0] = ix;
        out[1] = iy;
        out[2] = iz;
        return 1;
      }

      if(mx < my) {
        if(mx < mz) {
          ix += isx;
          mx += dx;
        } else {
          iz += isz;
          mz += dz;
        }
      } else {
        if(my < mz) {
          iy += isy;
          my += dy;
        } else {
          iz += isz;
          mz += dz;
        }
      }
    }
    return 0;
  }
#endif
