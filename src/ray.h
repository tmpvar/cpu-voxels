#ifndef __RAY__
#define __RAY__

#include <3d.h>
#include <immintrin.h>

typedef struct ray_t
{
  //common variables
  vec3 invdir;
  vec3 origin;
  // ray slope
  int classification;
} ray3;

typedef struct ray_packet_t {
  // stored as [0]=x, [1]=y, [2]=z
  vec3 invdir[4];
  vec3 origin[3];
} ray_packet3;

#endif
