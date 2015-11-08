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

uint8_t ray_isect(ray3 *r, vec3 ro, vec3 rd, aabb b) {
  float tx1 = (b[0][0] - ro[0])*r->ii;
  float tx2 = (b[1][0] - ro[0])*r->ii;

  float tmin = min(tx1, tx2);
  float tmax = max(tx1, tx2);

  float ty1 = (b[0][1] - ro[1])*r->ij;
  float ty2 = (b[1][1] - ro[1])*r->ij;

  tmin = max(tmin, min(ty1, ty2));
  tmax = min(tmax, max(ty1, ty2));

  float tz1 = (b[0][2] - ro[2])*r->ik;
  float tz2 = (b[1][2] - ro[2])*r->ik;

  tmin = max(tmin, min(tz1, tz2));
  tmax = min(tmax, max(tz1, tz2));

  return tmax >= max(0.0, tmin);
}

static float ray_aabb_lerp(ray3 *r, vec3 ro, aabb box, vec3 norm) {

  float a = 0, b = 0, c = 0;

  switch (r->classification) {
    case MMM:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;
      c = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ? 1 : 0;
      norm[1] = (b >= c && b >= a) ? 1 : 0;
      norm[2] = (c >= a && c >= b) ? 1 : 0;

      return max(max(a, b), c);
    break;

    case MMP:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;
      c = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      return max(max(a, b), c);
    break;

    case MPM:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;
      c = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      return max(max(a, b), c);
    break;

    case MPP:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;
      c = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ?  1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      return max(max(a, b), c);
    break;

    case PMM:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;
      c = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      return max(max(a, b), c);
    break;

    case PMP:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;
      c = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ?  1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      return max(max(a, b), c);
    break;

    case PPM:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;
      c = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ?  1 : 0;

      return max(max(a, b), c);
    break;

    case PPP:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;
      c = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b && a >= c) ? -1 : 0;
      norm[1] = (b >= c && b >= a) ? -1 : 0;
      norm[2] = (c >= a && c >= b) ? -1 : 0;

      return max(max(a, b), c);
    break;

    case OMM:
      a = (box[1][1] - ro[1]) * r->ij;
      b = (box[1][2] - ro[2]) * r->ik;

      norm[0] = 0;
      norm[1] = (a >= b) ? 1 : 0;
      norm[2] = (b >= a) ? 1 : 0;

      return max(a, b);
    break;

    case OMP:
      norm[0] = 0;
      norm[1] = (a >= b) ?  1 : 0;
      norm[2] = (b >= a) ? -1 : 0;

      return max(a, b);
    break;

    case OPM:
      a = (box[0][1] - ro[1]) * r->ij;
      b = (box[1][2] - ro[2]) * r->ik;

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ?  1 : 0;

      return max(a, b);
    break;

    case OPP:
      a = (box[0][1] - ro[1]) * r->ij;
      b = (box[0][2] - ro[2]) * r->ik;

      norm[0] = 0;
      norm[1] = (a >= b) ? -1 : 0;
      norm[2] = (b >= a) ? -1 : 0;

      return max(a, b);
    break;

    case MOM:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? 1 : 0;

      return max(a, b);
    break;

    case MOP:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      return max(a, b);
    break;

    case POM:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[1][2] - ro[2]) * r->ik;

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ?  1 : 0;

      return max(a, b);
    break;

    case POP:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[0][2] - ro[2]) * r->ik;

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = 0;
      norm[2] = (b >= a) ? -1 : 0;

      return max(a, b);
    break;

    case MMO:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;

      norm[0] = (a >= b) ? 1 : 0;
      norm[1] = (b >= a) ? 1 : 0;
      norm[2] = 0;

      return max(a, b);
    break;

    case MPO:
      a = (box[1][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;

      norm[0] = (a >= b) ?  1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      return max(a, b);
    break;

    case PMO:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[1][1] - ro[1]) * r->ij;

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ?  1 : 0;
      norm[2] = 0;

      return max(a, b);
    break;

    case PPO:
      a = (box[0][0] - ro[0]) * r->ii;
      b = (box[0][1] - ro[1]) * r->ij;

      norm[0] = (a >= b) ? -1 : 0;
      norm[1] = (b >= a) ? -1 : 0;
      norm[2] = 0;

      return max(a, b);
    break;

    case MOO:
      norm[0] = 1;
      norm[1] = norm[2] = 0;
      return (box[1][0] - ro[0]) * r->ii;
    break;

    case POO:
      norm[0] = -1;
      norm[1] = norm[2] = 0;
      return (box[0][0] - ro[0]) * r->ii;
    break;

    case OMO:
      norm[0] = 0;
      norm[1] = 1;
      norm[2] = 0;
      return (box[1][1] - ro[1]) * r->ij;
    break;

    case OPO:
      norm[0] = 0;
      norm[1] = -1;
      norm[2] = 0;
      return (box[0][1] - ro[1]) * r->ij;
    break;

    case OOM:
      norm[0] = norm[1] = 0;
      norm[2] = 1;
      return (box[1][2] - ro[2]) * r->ik;
    break;

    case OOP:
      norm[0] = norm[1] = 0;
      norm[2] = -1;
      return (box[0][2] - ro[2]) * r->ik;
    break;
  }

  norm[0] = norm[1] = norm[2] = 0;
  return -1;
}

#endif
