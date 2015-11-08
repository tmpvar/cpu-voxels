#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <3d.h>

void vec3_print(vec3 v) {
  printf("(%f, %f, %f)\n", v[0], v[1], v[2]);
}

int main() {

  printf("running\n");

  vec3 zero = vec3_create(0.0, 0.0, 0.0);
  vec3 a    = vec3_create(1.0, 2.0, 3.0);
  vec3 b    = vec3_create(5.0, 5.0, 5.0);
  vec3 c    = vec3_create(1.0, 0.0, 0.0);
  vec3 inva = vec3_create(1.0 / 1, 1.0 / 2, 1.0 / 3);


  vec3_print(a + b);

  vec3_print(vec3_reciprocal(a));
  vec3_print(inva);

  assert(vec3_distance(c, zero) == 1.0);
  printf("distance from 0,0,0 -> 1,0,0 = %f\n", vec3_distance(c, zero));

  return 0;
}
