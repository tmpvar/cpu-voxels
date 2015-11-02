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

uint8_t ray_isect(vec3 ro, vec3 rd, aabb b) {
    vec3 inv = {
      1.0 / rd[0],
      1.0 / rd[1],
      1.0 / rd[2]
    };

    double t1 = (b[0][0] - ro[0]) * inv[0];
    double t2 = (b[1][0] - ro[0]) * inv[0];

    double tmin = min(t1, t2);
    double tmax = max(t1, t2);

    for (int i = 1; i < 3; ++i) {
        t1 = (b[0][i] - ro[i]) * inv[i];
        t2 = (b[1][i] - ro[i]) * inv[i];

        tmin = max(tmin, min(t1, t2));
        tmax = min(tmax, max(t1, t2));
    }

    return tmax > max(tmin, 0.0);
}


uint8_t ray_aabb(ray3 *r, aabb b, double *t){

  switch (r->classification)
  {
  case MMM:
    {
      *t = (b[1][0] - r->x) * r->ii;
      double t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }


  case MMP:
    {
    *t = (b[1][0] - r->x) * r->ii;
      double t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case MPM:
    {
    *t = (b[1][0] - r->x) * r->ii;
    double t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;
    double t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case MPP:
    {
    *t = (b[1][0] - r->x) * r->ii;
      double t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PMM:
    {

    *t = (b[0][0] - r->x) * r->ii;
      double t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }


  case PMP:
    {
    *t = (b[0][0] - r->x) * r->ii;
      double t1 = (b[1][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PPM:
    {
    *t = (b[0][0] - r->x) * r->ii;
      double t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[1][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case PPP:
    {
    *t = (b[0][0] - r->x) * r->ii;
      double t1 = (b[0][1] - r->y) * r->ij;
      if(t1 > *t)
        *t = t1;
      double t2 = (b[0][2] - r->z) * r->ik;
      if(t2 > *t)
        *t = t2;

      return 1;
    }

  case OMM:
    {
    *t = (b[1][1] - r->y) * r->ij;
    double t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OMP:
    {
    *t = (b[1][1] - r->y) * r->ij;
    double t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OPM:
    {
    *t = (b[0][1] - r->y) * r->ij;
    double t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case OPP:
    {
    *t = (b[0][1] - r->y) * r->ij;
    double t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case MOM:
    {
    *t = (b[1][0] - r->x) * r->ii;
    double t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case MOP:
    {
    *t = (b[1][0] - r->x) * r->ii;
    double t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case POM:
    {
    *t = (b[0][0] - r->x) * r->ii;
    double t2 = (b[1][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }


  case POP:
    {
    *t = (b[0][0] - r->x) * r->ii;
    double t2 = (b[0][2] - r->z) * r->ik;
    if(t2 > *t)
      *t = t2;

    return 1;
    }

  case MMO:
    {
    *t = (b[1][0] - r->x) * r->ii;
    double t1 = (b[1][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }

  case MPO:
    {
    *t = (b[1][0] - r->x) * r->ii;
    double t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }


  case PMO:
    {
    *t = (b[0][0] - r->x) * r->ii;
    double t1 = (b[1][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }

  case PPO:
    {
    *t = (b[0][0] - r->x) * r->ii;
    double t1 = (b[0][1] - r->y) * r->ij;
    if(t1 > *t)
      *t = t1;

    return 1;
    }


  case MOO:
    {
    *t = (b[1][0] - r->x) * r->ii;
    return 1;
    }

  case POO:
    {
    *t = (b[0][0] - r->x) * r->ii;
    return 1;
    }

  case OMO:
    {
    *t = (b[1][1] - r->y) * r->ij;
    return 1;
    }

  case OPO:
    {
    *t = (b[0][1] - r->y) * r->ij;
    return 1;
    }


  case OOM:
    {
    *t = (b[1][2] - r->z) * r->ik;
    return 1;
    }

  case OOP:
    {
    *t = (b[0][2] - r->z) * r->ik;
    return 1;
    }
  }

  return 0;
}

static inline double ray_aabb_lerp(ray3 *r, vec3 ro, aabb box, vec3 norm) {

  double a, b, c;

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
