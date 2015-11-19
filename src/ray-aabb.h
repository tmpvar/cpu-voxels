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

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

#define rotatelps(ps)   _mm_shuffle_ps((ps),(ps), 0x39)

uint8_t ray_isect(ray3 *r, vec3 ro, vec3 rd, aabb b) {
  __m128 l1 = (b[0] - ro) * r->invdir;
  __m128 l2 = (b[1] - ro) * r->invdir;
  __m128 lmax = _mm_max_ps(l1, l2);
  __m128 lmin = _mm_min_ps(l1, l2);
  const __m128 lmax0 = rotatelps(lmax);
  const __m128 lmin0 = rotatelps(lmin);
  lmax = _mm_min_ss(lmax, lmax0);
  lmin = _mm_max_ss(lmin, lmin0);
  // float tx1 = (b[0][0] - ro[0])*r->invdir[0];
  // float tx2 = (b[1][0] - ro[0])*r->invdir[0];

  // float tmin = min(tx1, tx2);
  // float tmax = max(tx1, tx2);

  // float ty1 = (b[0][1] - ro[1])*r->invdir[1];
  // float ty2 = (b[1][1] - ro[1])*r->invdir[1];

  // tmin = max(tmin, min(ty1, ty2));
  // tmax = min(tmax, max(ty1, ty2));

  // float tz1 = (b[0][2] - ro[2])*r->invdir[2];
  // float tz2 = (b[1][2] - ro[2])*r->invdir[2];

  // tmin = max(tmin, min(tz1, tz2));
  // tmax = min(tmax, max(tz1, tz2));
  return _mm_comige_ss(lmax, _mm_setzero_ps()) & _mm_comige_ss(lmax,lmin);
  //return tmax >= max(0.0, tmin);
}

static vec3 ray_aabb_lerp(ray3 *r, vec3 ro, aabb box, float *t) {

  float a = 0, b = 0, c = 0;
  vec3 norm = vec3_create(0, 0, 0);

  switch (r->classification) {
    case MMM:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];
      c = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ? 1 : 0;
      norm[1] = (b >= c && b >= a) ? 1 : 0;
      norm[2] = (c >= a && c >= b) ? 1 : 0;

      *t = max(max(a, b), c);
    break;

    case MMP:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];
      c = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case MPM:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];
      c = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case MPP:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];
      c = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case PMM:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];
      c = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case PMP:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];
      c = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case PPM:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];
      c = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      *t = max(max(a, b), c);
    break;

    case PPP:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];
      c = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      *t = max(max(a, b), c);
    break;

    case OMM:
      a = (box[1][1] - ro[1]) * r->invdir[1];
      b = (box[1][2] - ro[2]) * r->invdir[2];

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
      a = (box[0][1] - ro[1]) * r->invdir[1];
      b = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ?  1 : 0;

      *t = max(a, b);
    break;

    case OPP:
      a = (box[0][1] - ro[1]) * r->invdir[1];
      b = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case MOM:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? 1 : 0;

      *t = max(a, b);
    break;

    case MOP:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case POM:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[1][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ?  1 : 0;

      *t = max(a, b);
    break;

    case POP:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[0][2] - ro[2]) * r->invdir[2];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      *t = max(a, b);
    break;

    case MMO:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = (b >= a) ? 1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case MPO:
      a = (box[1][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case PMO:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[1][1] - ro[1]) * r->invdir[1];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ?  1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case PPO:
      a = (box[0][0] - ro[0]) * r->invdir[0];
      b = (box[0][1] - ro[1]) * r->invdir[1];

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      *t = max(a, b);
    break;

    case MOO:
      norm[0] = 1;
      norm[1] = norm[2] = 0;
      *t = (box[1][0] - ro[0]) * r->invdir[0];
    break;

    case POO:
      norm[0] = -1;
      norm[1] = norm[2] = 0;
      *t = (box[0][0] - ro[0]) * r->invdir[0];
    break;

    case OMO:
      norm[0] = 0;
      norm[1] = 1;
      norm[2] = 0;
      *t = (box[1][1] - ro[1]) * r->invdir[1];
    break;

    case OPO:
      norm[0] = 0;
      norm[1] = -1;
      norm[2] = 0;
      *t = (box[0][1] - ro[1]) * r->invdir[1];
    break;

    case OOM:
      norm[0] = norm[1] = 0;
      norm[2] = 1;
      *t = (box[1][2] - ro[2]) * r->invdir[2];
    break;

    case OOP:
      norm[0] = norm[1] = 0;
      norm[2] = -1;
      *t = (box[0][2] - ro[2]) * r->invdir[2];
    break;
  }


  *t = -1;
  return norm;
}

#endif
