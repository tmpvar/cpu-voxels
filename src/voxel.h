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

  static int sign(const float a) {
    return a < 0 ? -1 : a > 0 ? 1 : 0;
  }

  static float diff(const float s, const float ds) {
    int is = (int)s;

    int r = s - (s < 0 ? -1 + is : is);
    return ds > 0 ? (1-r) / ds : r / -ds;
  }

  static int voxel_brick_traverse(
    voxel_brick *brick,
    const float ubx,
    const float uby,
    const float ubz,
    const vec3 isect,
    const vec3 rd,
    const float density,
    int *out)
  {
    float sx = sign(rd[0]);
    float sy = sign(rd[1]);
    float sz = sign(rd[2]);

    float x = isect[0];
    float y = isect[1];
    float z = isect[2];

    float mx = diff(x, rd[0]);
    float my = diff(y, rd[1]);
    float mz = diff(z, rd[2]);

    float dx = sx / rd[0];
    float dy = sy / rd[1];
    float dz = sz / rd[2];

    while (
      x >= -rd[0] && y >= -rd[1] && z >= -rd[2] &&
      x <= ubx && y <= uby && z <= ubz
    ) {

      unsigned int ix = (unsigned int)x;
      unsigned int iy = (unsigned int)y;
      unsigned int iz = (unsigned int)z;

      if (brick->voxels[ix][iy][iz] > density) {
        out[0] = ix;
        out[1] = iy;
        out[2] = iz;
        return 1;
      }

      if(mx < my) {
        if(mx < mz) {
          x += sx;
          mx += dx;
        } else {
          z += sz;
          mz += dz;
        }
      } else {
        if(my < mz) {
          y += sy;
          my += dy;
        } else {
          z += sz;
          mz += dz;
        }
      }
    }
    return 0;
  }
#endif
