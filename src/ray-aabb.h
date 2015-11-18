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

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

const __m256 zero = {
  0.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 0.0f
};

static inline int ray_isect_packet(const ray_packet3 packet, const aabb_packet b, __m256 *m) {
  __m256 invdir;
  __m256 lambda1;
  __m256 lambda2;
  __m256 lmin;
  __m256 lmax;

  // // X Axis
  invdir = packet.invdir[0];

  lambda1 = b[0] * invdir;
  lambda2 = b[3] * invdir;
  lmin = _mm256_min_ps(lambda1, lambda2);
  lmax = _mm256_max_ps(lambda1, lambda2);

  // // Y axis
  invdir = packet.invdir[1];

  lambda1 = b[1] * invdir;
  lambda2 = b[4] * invdir;
  lmin = _mm256_max_ps(_mm256_min_ps(lambda1, lambda2), lmin);
  lmax = _mm256_min_ps(_mm256_max_ps(lambda1, lambda2), lmax);

  // // Z axis
  invdir = packet.invdir[2];

  lambda1 = b[2] * invdir;
  lambda2 = b[5] * invdir;
  lmin = _mm256_max_ps(_mm256_min_ps(lambda1, lambda2), lmin);
  lmax = _mm256_min_ps(_mm256_max_ps(lambda1, lambda2), lmax);
  *m = lmin;
  return _mm256_movemask_ps(lmax >= _mm256_max_ps(zero, lmin));
}

#endif
