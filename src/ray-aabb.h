/******************************************************************************

  This source code accompanies the Journal of Graphics Tools paper:

  "Fast Ray-Axis-Aligned Bounding Box Overlap Tests using Ray Slopes"
  by Martin Eisemann and Marcus Magnor
  Computer Graphics Lab, TU Braunschweig, Germany

  This source code is public domain, but please mention us if you use it.

******************************************************************************/
#ifndef __RAY_AABB__
#define __RAY_AABB__

#include "ray.h"
#include "aabb.h"
#include "vec.h"
#include "voxel.h"
#include <xmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <avxintrin.h>

const __m128 zero = { 0.0f, 0.0f, 0.0f };

static inline int ray_isect_packet(ray_packet3 packet, const voxel_brick brick, const vec3 ro, vec3 *m) {
  vec3 invdir;
  vec3 lambda1;
  vec3 lambda2;
  vec3 lmin;
  vec3 lmax;

  aabb_packet b;
  b[0] = _mm_sub_ps(brick->bounds_packet[0], vec3f(ro[0]));
  b[1] = _mm_sub_ps(brick->bounds_packet[1], vec3f(ro[1]));
  b[2] = _mm_sub_ps(brick->bounds_packet[2], vec3f(ro[2]));
  b[3] = _mm_sub_ps(brick->bounds_packet[3], vec3f(ro[0]));
  b[4] = _mm_sub_ps(brick->bounds_packet[4], vec3f(ro[1]));
  b[5] = _mm_sub_ps(brick->bounds_packet[5], vec3f(ro[2]));

  // X Axis
  invdir = packet.invdir[0];

  lambda1 = b[0] * invdir;
  lambda2 = b[3] * invdir;
  lmin = _mm_min_ps(lambda1, lambda2);
  lmax = _mm_max_ps(lambda1, lambda2);

  // Y axis
  invdir = packet.invdir[1];

  lambda1 = b[1] * invdir;
  lambda2 = b[4] * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);

  // Z axis
  invdir = packet.invdir[2];

  lambda1 = b[2] * invdir;
  lambda2 = b[5] * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);
  *m = lmin;
  return _mm_movemask_ps(lmax >= _mm_max_ps(zero, lmin));
}

uint8_t ray_isect(ray3 *r, aabb b, float *m) {
  float tx1 = (b[0][0] - r->origin[0]) * r->invdir[0];
  float tx2 = (b[1][0] - r->origin[0]) * r->invdir[0];

  float tmin = fminf(tx1, tx2);
  float tmax = fmaxf(tx1, tx2);

  float ty1 = (b[0][1] - r->origin[1]) * r->invdir[1];
  float ty2 = (b[1][1] - r->origin[1]) * r->invdir[1];

  tmin = fmaxf(tmin, fminf(ty1, ty2));
  tmax = fminf(tmax, fmaxf(ty1, ty2));

  float tz1 = (b[0][2] - r->origin[2])*r -> invdir[2];
  float tz2 = (b[1][2] - r->origin[2])*r -> invdir[2];

  tmin = fmaxf(tmin, fminf(tz1, tz2));
  tmax = fminf(tmax, fmaxf(tz1, tz2));

  *m = tmin;

  return tmax >= fmaxf(0.0, tmin);
}

#endif
