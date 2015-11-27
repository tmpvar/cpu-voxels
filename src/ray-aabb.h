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

static inline int ray_isect(const ray3 *r, const aabb b, vec3 *out) {
  const vec3 x = _mm_min_ps(
    (b[0] - r->origin) * r->invdir,
    (b[1] - r->origin) * r->invdir
  );

  const vec3 max2 = _mm_max_ps(x, _mm_shuffle_ps(x, x, _MM_SHUFFLE(0,0,3,2)));
  const float tmin = _mm_cvtss_f32(_mm_max_ps(max2, _mm_shuffle_ps(max2, max2, _MM_SHUFFLE(0,0,0,1))));

  if (tmin > 0.0f) {
    *out = r->origin + r->dir * vec3f(tmin);
    return 1;
  } else {
    return 0;
  }
}

#endif
