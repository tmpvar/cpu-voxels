#ifndef __AABB__
#define __AABB__
  #include <stdio.h>
  #include "vec.h"

  typedef vec3 aabb[2];

  typedef vec3 aabb_packet[6];

  vec3 point_five = {0.5f, 0.5f, 0.5f};
  static inline vec3 aabb_center(aabb b) {
    return (b[0] + b[1]) * point_five;
  }

  static void aabb_print(aabb b) {
    printf("aabb (%f, %f, %f) -> (%f, %f, %f)\n",
      b[0][0], b[0][1], b[0][2],
      b[1][0], b[1][1], b[1][2]
    );
  }

  static int aabb_contains(aabb b, vec3 p) {
    return p[0] >= b[0][0] && p[0] <= b[1][0] &&
           p[1] >= b[0][1] && p[1] <= b[1][1] &&
           p[2] >= b[0][2] && p[2] <= b[1][2];

    // TODO: move back to simd when we can get the 4th component
    //       under control.  In it's current form, it causes octree
    //       creation to break.
    // return _mm_movemask_ps(p >= b[0] && p <= b[1]) == 0b1111;
  }
#endif
