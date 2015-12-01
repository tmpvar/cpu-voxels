#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "gtest/gtest.h"

#include "ray.h"
#include "aabb.h"
#include "ray-aabb.h"
#include "voxel.h"
#include "voxel-scene.h"
#include "vec.h"

#include "test-octree.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
