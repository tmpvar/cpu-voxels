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
#include <3d.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#include <avxintrin.h>

const __m128 zero = { 0.0f, 0.0f, 0.0f };

static inline int ray_isect_packet(ray_packet3 packet, aabb_packet b, vec3 *m) {
  vec3 invdir;
  vec3 lambda1;
  vec3 lambda2;
  vec3 lmin;
  vec3 lmax;

  // X Axis
  invdir = packet.invdir[0];

  lambda1 = lambda1 = b[0] * invdir;
  lambda2 = lambda2 = b[3] * invdir;
  lmin = _mm_min_ps(lambda1, lambda2);
  lmax = _mm_max_ps(lambda1, lambda2);

  // Y axis
  invdir = packet.invdir[1];

  lambda1 = lambda1 = b[1] * invdir;
  lambda2 = lambda2 = b[4] * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);

  // Z axis
  invdir = packet.invdir[2];

  lambda1 = lambda1 = b[2] * invdir;
  lambda2 = lambda2 = b[5] * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);
  *m = lmin;
  return _mm_movemask_ps(lmax >= _mm_max_ps(zero, lmin));
}

#endif
