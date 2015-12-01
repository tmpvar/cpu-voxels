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

const vec3 zero = { 0.0f, 0.0f, 0.0f };

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

static inline int ray_isect(ray3 *r, aabb b, vec3 *out) {
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

  // *m = tmin;
  *out = r->origin + r->dir * vec3f(tmin);
  return tmax >= fmaxf(0.0, tmin);
}

// turn those verbose intrinsics into something readable.
#define loadps(mem)   _mm_load_ps((const float * const)(mem))
#define storess(ss,mem)   _mm_store_ss((float * const)(mem),(ss))
#define minss     _mm_min_ss
#define maxss     _mm_max_ss
#define minps     _mm_min_ps
#define maxps     _mm_max_ps
#define mulps     _mm_mul_ps
#define subps     _mm_sub_ps
#define rotatelps(ps)   _mm_shuffle_ps((ps),(ps), 0x39) // a,b,c,d -> b,c,d,a
#define muxhps(low,high)  _mm_movehl_ps((low),(high)) // low{a,b,c,d}|high{e,f,g,h} = {c,d,g,h}


static const float flt_plus_inf = INFINITY; // let's keep C and C++ compilers happy.
static const float ps_cst_plus_inf[4]  = {  flt_plus_inf,  flt_plus_inf,  flt_plus_inf,  flt_plus_inf },
  ps_cst_minus_inf[4] = { -flt_plus_inf, -flt_plus_inf, -flt_plus_inf, -flt_plus_inf };

static int ray_isect_simd(ray3 *r, aabb b, vec3 *out) {
  // you may already have those values hanging around somewhere
  const vec3
    plus_inf  = loadps(ps_cst_plus_inf),
    minus_inf = loadps(ps_cst_minus_inf);

  // use whatever's apropriate to load.
  const vec3
    box_min = loadps(&b[0]),
    box_max = loadps(&b[1]),
    pos = loadps(&r->origin),
    inv_dir = loadps(&r->invdir);

  // use a div if inverted directions aren't available
  const vec3 l1 = mulps(subps(box_min, pos), inv_dir);
  const vec3 l2 = mulps(subps(box_max, pos), inv_dir);

  // the order we use for those min/max is vital to filter out
  // NaNs that happens when an inv_dir is +/- inf and
  // (box_min - pos) is 0. inf * 0 = NaN
  const vec3 filtered_l1a = minps(l1, plus_inf);
  const vec3 filtered_l2a = minps(l2, plus_inf);

  const vec3 filtered_l1b = maxps(l1, minus_inf);
  const vec3 filtered_l2b = maxps(l2, minus_inf);

  // now that we're back on our feet, test those slabs.
  vec3 lmax = maxps(filtered_l1a, filtered_l2a);
  vec3 lmin = minps(filtered_l1b, filtered_l2b);

  // unfold back. try to hide the latency of the shufps & co.
  const vec3 lmax0 = rotatelps(lmax);
  const vec3 lmin0 = rotatelps(lmin);
  lmax = minss(lmax, lmax0);
  lmin = maxss(lmin, lmin0);

  const vec3 lmax1 = muxhps(lmax,lmax);
  const vec3 lmin1 = muxhps(lmin,lmin);
  lmax = minss(lmax, lmax1);
  lmin = maxss(lmin, lmin1);

  const int ret = _mm_comige_ss(lmax, _mm_setzero_ps()) & _mm_comige_ss(lmax,lmin);

  *out = r->origin + r->dir * vec3f(lmin[0]);
  return  ret;
}


#endif
