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

uint8_t ray_isect(ray3 *r, aabb b) {
  vec3 lb = (b[0] - r->origin) * r->invdir;
  vec3 ub = (b[1] - r->origin) * r->invdir;

  float tx1 = lb[0];//(b[0][0] - ro[0])*r->invdir[0];
  float tx2 = ub[0];//(b[1][0] - ro[0])*r->invdir[0];

  float tmin = min(tx1, tx2);
  float tmax = max(tx1, tx2);

  float ty1 = lb[1];//(b[0][1] - ro[1])*r->invdir[1];
  float ty2 = ub[1];//(b[1][1] - ro[1])*r->invdir[1];

  tmin = max(tmin, min(ty1, ty2));
  tmax = min(tmax, max(ty1, ty2));

  float tz1 = lb[2];//(b[0][2] - ro[2])*r->invdir[2];
  float tz2 = ub[2];//(b[1][2] - ro[2])*r->invdir[2];

  tmin = max(tmin, min(tz1, tz2));
  tmax = min(tmax, max(tz1, tz2));

  return tmax >= max(0.0, tmin);
}

__m128 zero = { 0.0f, 0.0f, 0.0f };
int ray_isect_packet(ray_packet3 packet, aabb b, vec3 *m) {
  // TODO: bundle 4 rays together
  vec3 origin;
  vec3 invdir;
  vec3 lambda1;
  vec3 lambda2;
  vec3 lmin;
  vec3 lmax;

  // X Axis
  origin = packet.origin[0];
  invdir = packet.invdir[0];
  lambda1 = (_mm_permute_ps(b[0], _MM_SHUFFLE(0, 0, 0, 0)) - origin) * invdir;
  lambda2 = (_mm_permute_ps(b[1], _MM_SHUFFLE(0, 0, 0, 0)) - origin) * invdir;
  lmin = _mm_min_ps(lambda1, lambda2);
  lmax = _mm_max_ps(lambda1, lambda2);

  // Y axis
  origin = packet.origin[1];
  invdir = packet.invdir[1];

  lambda1 = (_mm_permute_ps(b[0], _MM_SHUFFLE(1, 1, 1, 1)) - origin) * invdir;
  lambda2 = (_mm_permute_ps(b[1], _MM_SHUFFLE(1, 1, 1, 1)) - origin) * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);

  // Z axis
  origin = packet.origin[2];
  invdir = packet.invdir[2];

  lambda1 = (_mm_permute_ps(b[0], _MM_SHUFFLE(2, 2, 2, 2)) - origin) * invdir;
  lambda2 = (_mm_permute_ps(b[1], _MM_SHUFFLE(2, 2, 2, 2)) - origin) * invdir;
  lmin = _mm_max_ps(_mm_min_ps(lambda1, lambda2), lmin);
  lmax = _mm_min_ps(_mm_max_ps(lambda1, lambda2), lmax);
  *m = lmin;
  return _mm_movemask_ps(lmax >= _mm_max_ps(zero, lmin));
}


static vec3 ray_aabb_lerp(vec3 ro, vec3 invdir, uint8_t classification, aabb box, float *t) {

  float a = 0, b = 0, c = 0;
  vec3 norm = vec3_create(0, 0, 0);

  switch (classification) {
    case MMM:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];
      c = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ? 1 : 0;
      norm[1] = (b >= c && b >= a) ? 1 : 0;
      norm[2] = (c >= a && c >= b) ? 1 : 0;

      *t = max(max(a, b), c);
    break;

    case MMP:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];
      c = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case MPM:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];
      c = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case MPP:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];
      c = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case PMM:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];
      c = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case PMP:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];
      c = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case PPM:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];
      c = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case PPP:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];
      c = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case OMM:
      a = (box[1][1] - ro[1]) * invdir[1];
      b = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = 0;
      norm[1] = (a >= b) ? 1 : 0;
      norm[2] = (b >= a) ? 1 : 0;

      *t = max(a, b);
    break;

    case OMP:
      norm[0] = 0;
      norm[1] = (a >= b) ?  1 : 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case OPM:
      a = (box[0][1] - ro[1]) * invdir[1];
      b = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ?  1 : 0;

      *t = max(a, b);
    break;

    case OPP:
      a = (box[0][1] - ro[1]) * invdir[1];
      b = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case MOM:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? 1 : 0;

      *t = max(a, b);
    break;

    case MOP:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case POM:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[1][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ?  1 : 0;

      *t = max(a, b);
    break;

    case POP:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[0][2] - ro[2]) * invdir[2];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case MMO:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = (b >= a) ? 1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case MPO:
      a = (box[1][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case PMO:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[1][1] - ro[1]) * invdir[1];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ?  1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case PPO:
      a = (box[0][0] - ro[0]) * invdir[0];
      b = (box[0][1] - ro[1]) * invdir[1];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case MOO:
      norm[0] = 1;
      norm[1] = norm[2] = 0;
      *t = (box[1][0] - ro[0]) * invdir[0];
    break;

    case POO:
      norm[0] = -1;
      norm[1] = norm[2] = 0;
      *t = (box[0][0] - ro[0]) * invdir[0];
    break;

    case OMO:
      norm[0] = 0;
      norm[1] = 1;
      norm[2] = 0;
      *t = (box[1][1] - ro[1]) * invdir[1];
    break;

    case OPO:
      norm[0] = 0;
      norm[1] = -1;
      norm[2] = 0;
      *t = (box[0][1] - ro[1]) * invdir[1];
    break;

    case OOM:
      norm[0] = norm[1] = 0;
      norm[2] = 1;
      *t = (box[1][2] - ro[2]) * invdir[2];
    break;

    case OOP:
      norm[0] = norm[1] = 0;
      norm[2] = -1;
      *t = (box[0][2] - ro[2]) * invdir[2];
    break;
  }


  *t = -1;
  return norm;
}

#endif
