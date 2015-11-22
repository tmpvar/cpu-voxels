#include <stdio.h>
#include "ray.h"
#include "ray-aabb.h"
#include "voxel.h"
#include "vec.h"

int main() {

  voxel_brick brick;
  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);
  voxel_brick_position(&brick, center);
  voxel_brick_fill_constant(&brick, 0.0f);
  voxel_brick_set(
    &brick,
    VOXEL_BRICK_WIDTH-1,
    VOXEL_BRICK_WIDTH-1,
    VOXEL_BRICK_WIDTH-1,
    100.0f
  );

  voxel_brick_fill_constant(&brick, 0.0f);
  voxel_brick_set(
    &brick,
    VOXEL_BRICK_HALF_WIDTH-1,
    VOXEL_BRICK_HALF_WIDTH-1,
    VOXEL_BRICK_HALF_WIDTH-1,
    100.0f
  );


  ray3 r;
  vec3 rd = { 1.0f, 1.0f, 1.0f };
  r.origin = vec3f(-0.5f);
  r.invdir = vec3_reciprocal(rd);

  float t = 0;

  uint8_t result = ray_isect(&r, brick.bounds, &t);

  if (result) {
    vec3 isect = r.origin + rd * vec3f(t);
    printf("isect: (%f, %f, %f)\n", isect[0], isect[1], isect[2]);

    printf("voxel cell: (%i, %i, %i)\n",
      (int)clamp(floor(isect[0] / VOXEL_SIZE), 0, VOXEL_BRICK_WIDTH-1),
      (int)clamp(floor(isect[1] / VOXEL_SIZE), 0, VOXEL_BRICK_WIDTH-1),
      (int)clamp(floor(isect[2] / VOXEL_SIZE), 0, VOXEL_BRICK_WIDTH-1)
    );

    int voxel_pos[3];
    int found = voxel_brick_traverse(
      &brick,
      isect,
      rd,
      1.0f,
      voxel_pos
    );

    printf("voxel: (%i, %i, %i)\n", voxel_pos[0], voxel_pos[1], voxel_pos[2]);

  }

  printf("FOUND? %i\n", result);
  return 0;
}
