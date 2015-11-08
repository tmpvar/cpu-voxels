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

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)

uint8_t ray_isect(ray3 *r, vec3 ro, vec3 rd, aabb b) {
  float tx1 = (b[0][0] - ro[0])*r->invdir[0];
  float tx2 = (b[1][0] - ro[0])*r->invdir[0];

  float tmin = min(tx1, tx2);
  float tmax = max(tx1, tx2);

  float ty1 = (b[0][1] - ro[1])*r->invdir[1];
  float ty2 = (b[1][1] - ro[1])*r->invdir[1];

  tmin = max(tmin, min(ty1, ty2));
  tmax = min(tmax, max(ty1, ty2));

  float tz1 = (b[0][2] - ro[2])*r->invdir[2];
  float tz2 = (b[1][2] - ro[2])*r->invdir[2];

  tmin = max(tmin, min(tz1, tz2));
  tmax = min(tmax, max(tz1, tz2));

  return tmax >= max(0.0, tmin);
}

uint8_t ray_isect1(ray3 *r, vec3 ro, vec3 rd, aabb b) {

  vec3 lb = (b[0] - ro) * r->invdir;
  vec3 ub = (b[1] - ro) * r->invdir;

  // vec3 vmax = vec3_max(lb, ub);
  // vec3 vmin = vec3_min(lb, ub);

  // float tx1 = (b[0][0] - ro[0])*r->invdir[0];
  // float tx2 = (b[1][0] - ro[0])*r->invdir[0];

  float tmin = min(lb[0], ub[0]);
  float tmax = max(lb[0], ub[0]);

  // float ty1 = (b[0][1] - ro[1])*r->invdir[1];
  // float ty2 = (b[1][1] - ro[1])*r->invdir[1];

  tmin = max(tmin, min(lb[1], ub[1]));
  tmax = min(tmax, max(lb[1], ub[1]));

  tmin = max(tmin, min(lb[2], ub[2]));
  tmax = min(tmax, max(lb[2], ub[2]));

  // float tz1 = (b[0][2] - ro[2])*r->invdir[2];
  // float tz2 = (b[1][2] - ro[2])*r->invdir[2];

  // float tmin = max(vmin[0], max(vmin[1], vmin[2]));
  // float tmax = min(vmax[0], max(vmax[1], vmax[2]));

  return tmax >= max(0.0, tmin);
}
/*
uint8_t ray_isect3(ray3 *r, vec3 ro, vec3 rd, aabb b) {
  // TODO: bundle 4 rays together
  float4 origin = rays.origins(X);
  float4 invDir = rays.invDirs(X);

  vec3 lambda1;
  vec3 lambda2;

  vec3 lmin;
  vec3 lmax;

  lmin = vec3_min(lambda1, lambda2);
  lmax = vec3_max(lambda1, lambda2);

  for (int axis = 0; axis <= 3; axis++) {
  origin = rays.origins(axis);
  invDir = rays.invDirs(axis);
  lambda1 = (_mm_shuffle_ps(b[0], ro, 0xFF - origin) * ray->invdir;
  lambda2 = (_mm_shuffle_ps(b[1], ro, 0xFF - origin) * ray->invdir;
  lmin = max(min(lambda1, lambda2), lmin);
  lmax = min(max(lambda1, lambda2), lmax);
  }
  return any(and(cmplt(lmin, lmax), cmpgt(lmax, 0)));

}
*/
// static float ray_aabb_lerp(ray3 *r, vec3 ro, aabb box, vec3 norm) {

//   float a, b, c;

//   switch (r->classification) {
//     case MMM:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;
//       c = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ? 1 : 0;
//       norm[1] = (b >= c && b >= a) ? 1 : 0;
//       norm[2] = (c >= a && c >= b) ? 1 : 0;

//       return max(max(a, b), c);
//     break;

//     case MMP:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;
//       c = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ?  1 : 0;
//       norm[1] = (b >= c && b >= a) ?  1 : 0;
//       norm[2] = (c >= a && c >= b) ? -1 : 0;

//       return max(max(a, b), c);
//     break;

//     case MPM:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;
//       c = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ?  1 : 0;
//       norm[1] = (b >= c && b >= a) ? -1 : 0;
//       norm[2] = (c >= a && c >= b) ?  1 : 0;

//       return max(max(a, b), c);
//     break;

//     case MPP:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;
//       c = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ?  1 : 0;
//       norm[1] = (b >= c && b >= a) ? -1 : 0;
//       norm[2] = (c >= a && c >= b) ? -1 : 0;

//       return max(max(a, b), c);
//     break;

//     case PMM:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;
//       c = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ? -1 : 0;
//       norm[1] = (b >= c && b >= a) ?  1 : 0;
//       norm[2] = (c >= a && c >= b) ?  1 : 0;

//       return max(max(a, b), c);
//     break;

//     case PMP:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;
//       c = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ? -1 : 0;
//       norm[1] = (b >= c && b >= a) ?  1 : 0;
//       norm[2] = (c >= a && c >= b) ? -1 : 0;

//       return max(max(a, b), c);
//     break;

//     case PPM:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;
//       c = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ? -1 : 0;
//       norm[1] = (b >= c && b >= a) ? -1 : 0;
//       norm[2] = (c >= a && c >= b) ?  1 : 0;

//       return max(max(a, b), c);
//     break;

//     case PPP:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;
//       c = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b && a >= c) ? -1 : 0;
//       norm[1] = (b >= c && b >= a) ? -1 : 0;
//       norm[2] = (c >= a && c >= b) ? -1 : 0;

//       return max(max(a, b), c);
//     break;

//     case OMM:
//       a = (box[1][1] - ro[1]) * r->ij;
//       b = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = 0;
//       norm[1] = (a >= b) ? 1 : 0;
//       norm[2] = (b >= a) ? 1 : 0;

//       return max(a, b);
//     break;

//     case OMP:
//       norm[0] = 0;
//       norm[1] = (a >= b) ?  1 : 0;
//       norm[2] = (b >= a) ? -1 : 0;

//       return max(a, b);
//     break;

//     case OPM:
//       a = (box[0][1] - ro[1]) * r->ij;
//       b = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = 0;
//       norm[1] = (a >= b) ? -1 : 0;
//       norm[2] = (b >= a) ?  1 : 0;

//       return max(a, b);
//     break;

//     case OPP:
//       a = (box[0][1] - ro[1]) * r->ij;
//       b = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = 0;
//       norm[1] = (a >= b) ? -1 : 0;
//       norm[2] = (b >= a) ? -1 : 0;

//       return max(a, b);
//     break;

//     case MOM:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b) ? 1 : 0;
//       norm[1] = 0;
//       norm[2] = (b >= a) ? 1 : 0;

//       return max(a, b);
//     break;

//     case MOP:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b) ?  1 : 0;
//       norm[1] = 0;
//       norm[2] = (b >= a) ? -1 : 0;

//       return max(a, b);
//     break;

//     case POM:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[1][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b) ? -1 : 0;
//       norm[1] = 0;
//       norm[2] = (b >= a) ?  1 : 0;

//       return max(a, b);
//     break;

//     case POP:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[0][2] - ro[2]) * r->ik;

//       norm[0] = (a >= b) ? -1 : 0;
//       norm[1] = 0;
//       norm[2] = (b >= a) ? -1 : 0;

//       return max(a, b);
//     break;

//     case MMO:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;

//       norm[0] = (a >= b) ? 1 : 0;
//       norm[1] = (b >= a) ? 1 : 0;
//       norm[2] = 0;

//       return max(a, b);
//     break;

//     case MPO:
//       a = (box[1][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;

//       norm[0] = (a >= b) ?  1 : 0;
//       norm[1] = (b >= a) ? -1 : 0;
//       norm[2] = 0;

//       return max(a, b);
//     break;

//     case PMO:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[1][1] - ro[1]) * r->ij;

//       norm[0] = (a >= b) ? -1 : 0;
//       norm[1] = (b >= a) ?  1 : 0;
//       norm[2] = 0;

//       return max(a, b);
//     break;

//     case PPO:
//       a = (box[0][0] - ro[0]) * r->ii;
//       b = (box[0][1] - ro[1]) * r->ij;

//       norm[0] = (a >= b) ? -1 : 0;
//       norm[1] = (b >= a) ? -1 : 0;
//       norm[2] = 0;

//       return max(a, b);
//     break;

//     case MOO:
//       norm[0] = 1;
//       norm[1] = norm[2] = 0;
//       return (box[1][0] - ro[0]) * r->ii;
//     break;

//     case POO:
//       norm[0] = -1;
//       norm[1] = norm[2] = 0;
//       return (box[0][0] - ro[0]) * r->ii;
//     break;

//     case OMO:
//       norm[0] = 0;
//       norm[1] = 1;
//       norm[2] = 0;
//       return (box[1][1] - ro[1]) * r->ij;
//     break;

//     case OPO:
//       norm[0] = 0;
//       norm[1] = -1;
//       norm[2] = 0;
//       return (box[0][1] - ro[1]) * r->ij;
//     break;

//     case OOM:
//       norm[0] = norm[1] = 0;
//       norm[2] = 1;
//       return (box[1][2] - ro[2]) * r->ik;
//     break;

//     case OOP:
//       norm[0] = norm[1] = 0;
//       norm[2] = -1;
//       return (box[0][2] - ro[2]) * r->ik;
//     break;
//   }

//   norm[0] = norm[1] = norm[2] = 0;
//   return -1;
// }

#endif
