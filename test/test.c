#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "ray.h"
#include "aabb.h"
#include "ray-aabb.h"
#include "voxel.h"
#include "voxel-scene.h"
#include "vec.h"

#define EPS 1e-6

void ok(const int v, const char *msg) {
  if (!v) {
    printf("not ok: %s\n", msg);
    exit(1);
  }
}

int feq(const float a, const float b) {
  int r = fabsf(a - b) < EPS;
  if (!r) {
    printf("not ok: %f should be %f\n", a, b);
    exit(1);
  }
  return r;
}

int fneq(const float a, const float b) {
  int r = fabsf(a - b) > EPS;
  if (!r) {
    printf("not ok: %f should not be %f\n", a, b);
    exit(1);
  }
  return r;
}

int peq(const void *a, const void *b) {
  int r = a == b;
  if (!r) {
    printf("not ok: %p should be %p\n", a, b);
    exit(1);
  }
  return r;
}

int pneq(const void *a, const void *b) {
  int r = a != b;
  if (!r) {
    printf("not ok: %p should not be %p\n", a, b);
    exit(1);
  }
  return r;
}

void test_aabb() {
  aabb b = {
    vec3f(-1.0f),
    vec3f( 1.0f)
  };

  ok(!aabb_contains(b, vec3f(2.0f)), "aabb does not contain point");
  ok(aabb_contains(b, vec3f(0.0f)), "aabb contains point");
}


void test_basic_octree_creation() {
  voxel_brick brick = voxel_brick_create();

  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);
  voxel_brick_position(brick, center);
  voxel_brick_fill_constant(brick, 0.0f);

  voxel_scene scene = voxel_scene_create();
  voxel_scene_add_brick(scene, brick);

  feq(scene->root->bounds[0][0], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[0][1], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[0][2], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][0],  VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][1],  VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][2],  VOXEL_BRICK_SIZE);
}

void test_octree_brick_out_of_bounds() {
  voxel_brick brick = voxel_brick_create();

  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);
  voxel_brick_position(brick, center);
  voxel_brick_fill_constant(brick, 0.0f);

  voxel_scene scene = voxel_scene_create();
  voxel_scene_add_brick(scene, brick);

  feq(scene->root->bounds[0][0], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[0][1], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[0][2], -VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][0],  VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][1],  VOXEL_BRICK_SIZE);
  feq(scene->root->bounds[1][2],  VOXEL_BRICK_SIZE);

  bounding_tree_node old_root = scene->root;

  voxel_brick outside = voxel_brick_create();
  voxel_brick_position(outside, vec3f(VOXEL_BRICK_SIZE + VOXEL_BRICK_HALF_SIZE));
  voxel_brick_fill_constant(outside, 0.0f);

  voxel_scene_add_brick(scene, outside);

  ok(scene->root != old_root, "scene->root should get replaced");

  feq(scene->root->bounds[0][0], -VOXEL_BRICK_SIZE * 2.0f);
  feq(scene->root->bounds[0][1], -VOXEL_BRICK_SIZE * 2.0f);
  feq(scene->root->bounds[0][2], -VOXEL_BRICK_SIZE * 2.0f);
  feq(scene->root->bounds[1][0],  VOXEL_BRICK_SIZE * 2.0f);
  feq(scene->root->bounds[1][1],  VOXEL_BRICK_SIZE * 2.0f);
  feq(scene->root->bounds[1][2],  VOXEL_BRICK_SIZE * 2.0f);
}

int main() {

  test_aabb();

  test_basic_octree_creation();
  test_octree_brick_out_of_bounds();
/*
  voxel_brick brick = voxel_brick_create();

  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);
  voxel_brick_position(brick, center);
  voxel_brick_fill_constant(brick, 0.0f);
  voxel_brick_set(
    brick,
    VOXEL_BRICK_WIDTH-1,
    VOXEL_BRICK_WIDTH-1,
    VOXEL_BRICK_WIDTH-1,
    100.0f
  );

  voxel_scene scene = voxel_scene_create();
  voxel_scene_add_brick(scene, brick);


  ray3 r;
  vec3 rd = { 1.0f, 1.0f, 1.0f };
  r.origin = vec3f(-0.5f);
  r.invdir = vec3_reciprocal(rd);

  float t = 0;

  uint8_t result = ray_isect(&r, brick->bounds, &t);

  if (result) {
    vec3 isect = r.origin + rd * vec3f(t);
    printf("isect: (%f, %f, %f)\n", isect[0], isect[1], isect[2]);


    int voxel_pos[3];
    int found = voxel_brick_traverse(
      brick,
      isect,
      rd,
      1.0f,
      voxel_pos
    );

    printf("voxel: (%i, %i, %i)\n", voxel_pos[0], voxel_pos[1], voxel_pos[2]);

  }

  printf("FOUND? %i\n", result);
*/
  return 0;
}
