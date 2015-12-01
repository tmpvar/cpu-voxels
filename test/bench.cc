#include "ray.h"
#include "aabb.h"
#include "ray-aabb.h"
#include "voxel.h"
#include "voxel-scene.h"
#include "vec.h"

#include <string>
#include <benchmark/benchmark.h>

static void bench_voxel_scene_traverse_miss(benchmark::State& state) {
  int out, accumulator[3];
  ray3 r;
  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);

  r.origin = vec3_create(VOXEL_BRICK_HALF_SIZE, VOXEL_BRICK_HALF_SIZE, 1.0f);
  r.dir = vec3_norm(center - r.origin);
  r.invdir = vec3_reciprocal(r.dir);

  voxel_brick brick = voxel_brick_create();

  voxel_brick_position(brick, center);
  voxel_brick_fill_constant(brick, 0.0f);

  voxel_scene scene = voxel_scene_create();
  voxel_scene_add_brick(scene, brick);

  while (state.KeepRunning()) {
    voxel_scene_ray(scene, &r, accumulator);
  }
}

BENCHMARK(bench_voxel_scene_traverse_miss);

static void bench_ray_aabb(benchmark::State& state) {

  ray3 r;
  r.origin = vec3_create(0.0f, 0.0f, 1.0f);
  r.dir = vec3_norm(-r.origin);
  r.invdir = vec3_reciprocal(r.dir);

  aabb b;
  b[0] = vec3f(-1.0f);
  b[1] = vec3f( 1.0f);

  vec3 out;
  while (state.KeepRunning()) {
    ray_isect(&r, b, &out);
  }
}

BENCHMARK(bench_ray_aabb);


static void bench_ray_aabb_simd(benchmark::State& state) {

  ray3 r;
  r.origin = vec3_create(0.0f, 0.0f, 1.0f);
  r.dir = vec3_norm(-r.origin);
  r.invdir = vec3_reciprocal(r.dir);

  aabb b;
  b[0] = vec3f(-1.0f);
  b[1] = vec3f( 1.0f);

  vec3 out;
  while (state.KeepRunning()) {
    ray_isect_simd(&r, b, &out);
    (void)out;
  }
}

BENCHMARK(bench_ray_aabb_simd);

BENCHMARK_MAIN();
