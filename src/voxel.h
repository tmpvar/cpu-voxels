#ifndef __VOXEL__
#define __VOXEL__
  #include <string.h>
  #include <math.h>
  #include <float.h>
  #include "vec.h"
  #include "aabb.h"
  #include "swizzle.h"

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

  static inline float voxel_brick_get_vec3(voxel_brick brick, const vec3 p) {
    return brick->voxels[(int)p[0]*VOXEL_BRICK_WIDTH*VOXEL_BRICK_WIDTH + (int)p[1]*VOXEL_BRICK_WIDTH + (int)p[2]];
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

  float mfmod(const float x, const float y) { float a = x/y; return (a-(int)a)*y; }

  static inline float mod(const float value, const float modulus) {
    return mfmod(mfmod(value, modulus) + modulus, modulus);
  }

  static inline float intbound(float s, float ds) {
    if (ds < 0) {
      s = -s;
      ds = -ds;
    }

    s = mod(s, VOXEL_SIZE);
    return (VOXEL_SIZE-s)/ds;
  }

  // TODO: replace density with a callback?
  static int voxel_brick_traverse(
    voxel_brick brick,
    const vec3 isect,
    const vec3 rd,
    const float density,
    int *out
  ) {

    const vec3 zero = vec3f(0.0f);
    const vec3 voxel_brick_width = vec3f(VOXEL_BRICK_WIDTH);

    vec3 voxel_size = vec3f(VOXEL_SIZE);
    vec3 voxel_size_inv = _mm_rcp_ps(voxel_size);
    vec3 dir_sized = rd * voxel_size;
    vec3 dir_sign = vec3_sign(rd) * voxel_size;
    vec3 pos = (isect - brick->bounds[0]) + dir_sized;

    vec3 maxt = vec3_create(
      intbound(pos[0], dir_sized[0]),
      intbound(pos[1], dir_sized[1]),
      intbound(pos[2], dir_sized[2])
    );

    vec3 deltat = dir_sign / dir_sized;
    vec3 index = _mm_floor_ps(pos * voxel_size_inv);
    vec3 step = dir_sign * voxel_size_inv;
    vec3 mask;

    // compare with out of bounds scenario to make the comparison stupid simple (but inverted)
    while (!_mm_movemask_ps(_mm_or_ps(index < zero, index >= voxel_brick_width))) {

      if (voxel_brick_get_vec3(brick, index) > density) {
        out[0] = index[0];
        out[1] = index[1];
        out[2] = index[2];
        return 1;
      }

      mask = _mm_and_ps(
        _mm_cmplt_ps(maxt, _mm_swizzle_ps_yzxw(maxt)),
        _mm_cmple_ps(maxt, _mm_swizzle_ps_zxyw(maxt))
      );

      maxt += _mm_and_ps(mask, deltat);
      index += _mm_and_ps(mask, step);
    }
    return 0;
  }
#endif
