#include <gtest/gtest.h>

vec3 octants[8] = {
  {-VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE},
  {+VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE},
  {-VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE},
  {+VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE},
  {-VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE},
  {+VOXEL_BRICK_HALF_SIZE, -VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE},
  {-VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE},
  {+VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE, +VOXEL_BRICK_HALF_SIZE}
};

TEST(scene, one_cube) {
  voxel_scene scene = voxel_scene_create();

  vec3 center = vec3f(VOXEL_BRICK_HALF_SIZE);

  voxel_brick brick = voxel_brick_create();
  voxel_brick_position(brick, center);
  voxel_brick_fill_constant(brick, 0.0f);
  bounding_tree_node n = voxel_scene_add_brick(scene, brick);

  EXPECT_EQ(scene->root->bounds[0][0], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][1], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][2], 0.0f);
  EXPECT_EQ(scene->root->bounds[1][0], VOXEL_BRICK_SIZE * 2.0f);
  EXPECT_EQ(scene->root->bounds[1][1], VOXEL_BRICK_SIZE * 2.0f);
  EXPECT_EQ(scene->root->bounds[1][2], VOXEL_BRICK_SIZE * 2.0f);

  // ensure it is placed in the right octant
  EXPECT_EQ(scene->root->children[0], n);
}

TEST(scene, full_1_level_octree) {
  voxel_scene scene = voxel_scene_create();

  for (int i=0; i<8; i++) {
    voxel_brick brick = voxel_brick_create();
    voxel_brick_position(brick, scene->root->center + octants[i]);
    voxel_brick_fill_constant(brick, 0.0f);
    voxel_scene_add_brick(scene, brick);

    // ensure the brick is in the right octant
    EXPECT_EQ(scene->root->children[i]->brick, brick);

    // ensure the brick bounds and node bounds match
    EXPECT_EQ(
      scene->root->children[i]->bounds[0][0],
      scene->root->children[i]->brick->bounds[0][0]
    );
    EXPECT_EQ(
      scene->root->children[i]->bounds[0][1],
      scene->root->children[i]->brick->bounds[0][1]
    );
    EXPECT_EQ(
      scene->root->children[i]->bounds[0][2],
      scene->root->children[i]->brick->bounds[0][2]
    );
    EXPECT_EQ(
      scene->root->children[i]->bounds[1][0],
      scene->root->children[i]->brick->bounds[1][0]
    );
    EXPECT_EQ(
      scene->root->children[i]->bounds[1][1],
      scene->root->children[i]->brick->bounds[1][1]
    );
    EXPECT_EQ(
      scene->root->children[i]->bounds[1][2],
      scene->root->children[i]->brick->bounds[1][2]
    );
  }

  EXPECT_EQ(scene->root->bounds[0][0], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][1], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][2], 0.0f);
  EXPECT_EQ(scene->root->bounds[1][0], VOXEL_BRICK_SIZE * 2.0f);
  EXPECT_EQ(scene->root->bounds[1][1], VOXEL_BRICK_SIZE * 2.0f);
  EXPECT_EQ(scene->root->bounds[1][2], VOXEL_BRICK_SIZE * 2.0f);
}

TEST(scene, full_2_level_octree) {

  voxel_scene scene = voxel_scene_create();
  for (int i = 0; i < 8; i++) {
    vec3 octant_center = octants[i] * vec3f(2.0f);
    for (int j=0; j<8; j++) {

      voxel_brick brick = voxel_brick_create();
      voxel_brick_position(brick, octant_center + octants[j]);
      voxel_brick_fill_constant(brick, 0.0f);
      bounding_tree_node n = voxel_scene_add_brick(scene, brick);

      EXPECT_EQ(brick->bounds[0][0], n->bounds[0][0]);
      EXPECT_EQ(brick->bounds[0][1], n->bounds[0][1]);
      EXPECT_EQ(brick->bounds[0][2], n->bounds[0][2]);

      EXPECT_EQ(brick->bounds[1][0], n->bounds[1][0]);
      EXPECT_EQ(brick->bounds[1][1], n->bounds[1][1]);
      EXPECT_EQ(brick->bounds[1][2], n->bounds[1][2]);

      EXPECT_EQ(scene->root->children[i]->children[j]->brick, brick);
    }
  }

  EXPECT_EQ(scene->root->bounds[0][0], -VOXEL_BRICK_SIZE*2.0f);
  EXPECT_EQ(scene->root->bounds[0][1], -VOXEL_BRICK_SIZE*2.0f);
  EXPECT_EQ(scene->root->bounds[0][2], -VOXEL_BRICK_SIZE*2.0f);
  EXPECT_EQ(scene->root->bounds[1][0],  VOXEL_BRICK_SIZE*2.0f);
  EXPECT_EQ(scene->root->bounds[1][1],  VOXEL_BRICK_SIZE*2.0f);
  EXPECT_EQ(scene->root->bounds[1][2],  VOXEL_BRICK_SIZE*2.0f);
}

TEST(scene, three_level_brick_position) {
  voxel_scene scene = voxel_scene_create();
  bounding_tree_node n = scene->root;
  for (int i=0; i<3; i++) {
    voxel_brick brick = voxel_brick_create();
    voxel_brick_position(brick, vec3_create(
      scene->root->bounds[1][0] + VOXEL_BRICK_HALF_SIZE,// + (scene->root->level) * VOXEL_BRICK_SIZE,
      VOXEL_BRICK_HALF_SIZE,
      VOXEL_BRICK_HALF_SIZE
    ));
    voxel_brick_fill_constant(brick, 0.0f);
    n = voxel_scene_add_brick(scene, brick);
  }



  EXPECT_EQ(scene->root->bounds[0][0], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][1], 0.0f);
  EXPECT_EQ(scene->root->bounds[0][2], 0.0f);
  EXPECT_EQ(scene->root->bounds[1][0], VOXEL_BRICK_SIZE * 4.0f);
  EXPECT_EQ(scene->root->bounds[1][1], VOXEL_BRICK_SIZE * 4.0f);
  EXPECT_EQ(scene->root->bounds[1][2], VOXEL_BRICK_SIZE * 4.0f);
}
