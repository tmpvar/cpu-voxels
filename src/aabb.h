#ifndef __AABB__
#define __AABB__
  #include "vec.h"
  typedef vec3 aabb[2];

  typedef vec3 aabb_packet[6];

  vec3 two = {2.0f, 2.0f, 2.0f};
  static inline vec3 aabb_center(aabb b) {
    return (b[0] + b[1]) / two;
  }

#endif
