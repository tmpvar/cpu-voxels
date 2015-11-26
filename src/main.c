#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thpool.h>

#include "vec.h"
#include "aabb.h"
#include "ray.h"
#include "ray-aabb.h"
#include "orbit-camera.h"
#include "voxel.h"
#include "voxel-scene.h"

#define ENABLE_THREADS
#ifdef ENABLE_THREADS
  #define TOTAL_THREADS 7
#else
  #define TOTAL_THREADS 1
#endif

#define RENDER

struct {
  uint8_t down;
  float x, y;
} mouse;

static void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case  GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
      break;
    }
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

  mouse.down = action == GLFW_PRESS;
}

void mouse_move_callback(GLFWwindow* window, double x, double y) {

  if (mouse.down) {
    int w, h;
    glfwGetWindowSize(window, &w, &h);

    orbit_camera_rotate(0, 0, (mouse.x - x) / w, (mouse.y - y) / h);

    printf("here (%f, %f) -> (%f, %f)\n", mouse.x / w - 0.5,  mouse.y / h - 0.5, x/w-.5, y/h-.5);
  }

  mouse.x = x;
  mouse.y = y;
}

void vec3_print(const vec3 v) {
  printf("(%f, %f, %f)\n", v[0], v[1], v[2]);
}

typedef struct {
  uint8_t *data;
  int x;
  int y;
  int width;
  int height, screen_height;
  int stride;
  int render_id;
  vec3 pos;
  vec3 dcol;
  vec3 drow;
  vec3 ro;
  vec4 color;
  voxel_brick *bricks;
  voxel_scene scene;
  unsigned int brick_count;
} screen_area;

float brick_fill(const unsigned int x, const unsigned int y, const unsigned int z) {
  if (x == VOXEL_BRICK_HALF_WIDTH ||
      y == VOXEL_BRICK_HALF_WIDTH ||
      z == VOXEL_BRICK_HALF_WIDTH
  ) {
    return 100.0f;
  }

  float dx = x - VOXEL_BRICK_HALF_WIDTH;
  float dy = y - VOXEL_BRICK_HALF_WIDTH;
  float dz = z - VOXEL_BRICK_HALF_WIDTH;

  float d = sqrtf(dx*dx + dy*dy + dz*dz);
  if (d < VOXEL_BRICK_HALF_WIDTH) {
    return 100.0f;
  }
  // return x > 0 && x < VOXEL_BRICK_WIDTH-1 && y > 0 && y < VOXEL_BRICK_WIDTH-1 && z > 0 && z < VOXEL_BRICK_WIDTH-1 ? 100.0f : 0;//(x%2 == 0 && y%2 == 0 && z%2 == 0) ? 100.0f : 0.0f;

 return 0.0f;
}

void render_screen_area(void *args) {
  ray3 ray;
  float t = 0;

  screen_area *c = (screen_area *)args;
  int width = c->width;
  int height = c->height;
  int stride = c->stride;
  vec3 planeXPosition;

  vec3 dcol, drow, ro, rd, normal, o;
  dcol = c->dcol;
  drow = c->drow;
  ro = c->ro;
  uint8_t *data = c->data;
  ray_packet3 packet;
  packet.origin[0] = vec3f(ro[0]);
  packet.origin[1] = vec3f(ro[1]);
  packet.origin[2] = vec3f(ro[2]);
  vec3 planeYPosition = dcol * vec3f(c->y) + c->pos;
  vec3 invdir[4], dir[4];
  vec3 m;
  float r = VOXEL_BRICK_HALF_SIZE * 0.99f;
  int result;
  int x, y;
  ray.origin = ro;
  int cr, cg, cb;
  int voxel_pos[3];

  for (y=c->y; y<height; ++y) {
    planeXPosition = planeYPosition;
    for (x=0; x<width; x++) {
      unsigned long where = y * width * stride + x * stride;

      cr = (int)(((x)/(float)width) * 255);
      cg = (int)((y/(float)c->screen_height) * 255);
      cb = 0;

      planeXPosition += drow;
      ray.dir = planeXPosition - ro;
      ray.invdir = vec3_reciprocal(ray.dir);
      // TODO: return brick
      if (voxel_scene_ray(c->scene, &ray, voxel_pos)) {
        cr = (int)((voxel_pos[0] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
        cg = (int)((voxel_pos[1] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
        cb = (int)((voxel_pos[2] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
      }

      data[where+0] = cr;
      data[where+1] = cg;
      data[where+2] = cb;

      // for (int i=0; i<4; i++) {
      //   planeXPosition += drow;
      //   rd = planeXPosition - ro;
      //   dir[i] = rd;
      //   invdir[i] = vec3_reciprocal(rd);
      //   packet.invdir[0][i] = invdir[i][0];
      //   packet.invdir[1][i] = invdir[i][1];
      //   packet.invdir[2][i] = invdir[i][2];
      // }

      // result = 0;
      // for (int b=0; b<c->brick_count; b++) {

      //   int local_result = ray_isect_packet(packet, c->bricks[b], c->ro, &m);
      //   for (int j=0; j<4; j++) {
      //     unsigned long where = y * width * stride + (x + j) * stride;

      //     int cr = (int)(((x+j)/(float)width) * 255);
      //     int cg = (int)((y/(float)c->screen_height) * 255);
      //     int cb = 0;

      //     if (local_result & (1<<j)) {
      //       if (result & (1<<j)) { continue; }
      //       vec3 isect = ro + dir[j] * vec3f(m[j]);
      //       o = isect - c->bricks[b]->center;

      //       for (int k=0; k<3; k++) {
      //         if (fabsf(o[k]) >= r) {
      //           normal[k] = o[k] > 0.0f ? 1.0f : -1.0f;
      //         } else {
      //           normal[k] = 0.0f;
      //         }
      //       }

      //       float sum = fabsf(normal[0]) + fabsf(normal[1]) + fabsf(normal[2]);

      //       int voxel_pos[3] = { 0, 0, 0 };
      //       int found = voxel_brick_traverse(
      //         c->bricks[b],
      //         isect,
      //         vec3_norm(dir[j]),
      //         1.0f,
      //         voxel_pos
      //       );

      //       if (found) {
      //         cr = (int)((voxel_pos[0] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
      //         cg = (int)((voxel_pos[1] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
      //         cb = (int)((voxel_pos[2] / (float)VOXEL_BRICK_WIDTH) * 255.0f);
      //       } else {
      //         cr = fmaxf(0, cr - 20);
      //         cg = fmaxf(0, cg - 20);
      //         cb = fmaxf(0, cb - 20);
      //       }

      //       if (sum >= 2) {
      //         cr = fmaxf(0, cr - 20);
      //         cg = fmaxf(0, cg - 20);
      //         cb = fmaxf(0, cb - 20);
      //       }
      //     }

      //     if (!(result & (1<<j))) {
      //       data[where+0] = cr;
      //       data[where+1] = cg;
      //       data[where+2] = cb;
      //     }
      //   }

      //   result |= local_result;
      // }
    }
    planeYPosition += dcol;
  }
}

int main(void)
{

  _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
  _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

  int width = 800, height = 600;
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(width, height, "cpu-voxels", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, mouse_move_callback);
  glfwSetKeyCallback(window, key_callback);

  vec3 eye = vec3_create(0.0f, 0.0f, VOXEL_BRICK_SIZE * 4);
  vec3 center = vec3f(0.0f);
  vec3 up = vec3_create(0.0, 1.0, 0.0 );

  orbit_camera_init(eye, center, up);

  // TODO: handle resize

  int dw, dh;
  glfwGetFramebufferSize(window, &dw, &dh);
  int stride = 3;
  int total = dw*dh*stride;
  uint8_t *data = malloc(total);

  vec3 ro; //, rd;
  mat4 m4inverted, view;
  mat4 projection;
  mat4_perspective(
    projection,
    M_PI/4.0,
    (float)width/(float)height,
    0.1,
    1000.0
  );
  GLuint texture[1];

#ifdef ENABLE_THREADS
  screen_area areas[TOTAL_THREADS];
  threadpool thpool = thpool_init(TOTAL_THREADS);
#else
  screen_area areas[1];
#endif

  glGenTextures(1, texture);
  float start = glfwGetTime();
  int fps = 0;
  unsigned int brick_count = 8;
  voxel_brick my_first_brick[brick_count];

  my_first_brick[0] = voxel_brick_create();
  voxel_brick_position(my_first_brick[0], vec3f(VOXEL_BRICK_HALF_SIZE));
  voxel_brick_fill(my_first_brick[0], &brick_fill);

  my_first_brick[1] = voxel_brick_create();
  voxel_brick_position(my_first_brick[1], vec3f(-VOXEL_BRICK_HALF_SIZE));
  voxel_brick_fill(my_first_brick[1], &brick_fill);

  my_first_brick[2] = voxel_brick_create();
  voxel_brick_position(my_first_brick[2], vec3_create(
    -VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[2], &brick_fill);

  my_first_brick[3] = voxel_brick_create();
  voxel_brick_position(my_first_brick[3], vec3_create(
    -VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[3], &brick_fill);

  my_first_brick[4] = voxel_brick_create();
  voxel_brick_position(my_first_brick[4], vec3_create(
    -VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[4], &brick_fill);

  my_first_brick[5] = voxel_brick_create();
  voxel_brick_position(my_first_brick[5], vec3_create(
     VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[5], &brick_fill);

  my_first_brick[6] = voxel_brick_create();
  voxel_brick_position(my_first_brick[6], vec3_create(
     VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[6], &brick_fill);

  my_first_brick[7] = voxel_brick_create();
  voxel_brick_position(my_first_brick[7], vec3_create(
     VOXEL_BRICK_HALF_SIZE,
    -VOXEL_BRICK_HALF_SIZE,
     VOXEL_BRICK_HALF_SIZE
  ));
  voxel_brick_fill(my_first_brick[7], &brick_fill);


  voxel_scene scene = voxel_scene_create();
  for (int b = 0; b<brick_count; b++) {
    voxel_scene_add_brick(scene, my_first_brick[b]);
  }

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      orbit_camera_rotate(0, 0, -.1, 0);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      orbit_camera_rotate(0, 0, .1, 0);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      orbit_camera_rotate(0, 0, 0, .1);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      orbit_camera_rotate(0, 0, 0, -.1);
    }

    glfwGetFramebufferSize(window, &width, &height);
    float now = glfwGetTime();
    if (now - start > 1) {
      unsigned long long total_rays = (fps * width * height);
      printf("fps: %i (%f Mrays/s)@%ix%i - %i threads\n", fps, total_rays/1000000.0, width, height, TOTAL_THREADS);
      start = now;
      fps = 0;
    }
    fps++;


    orbit_camera_view(view);
    ro = mat4_get_eye(view);

    mat4_mul(m4inverted, projection, view);
    mat4_invert(m4inverted, m4inverted);

    // compute 3 points so that we can interpolate instead of unprojecting
    // on every point
    vec3 rda, rdb, planeYPosition, dcol, drow;

    vec3 t0 = vec3_create(0, 0, 0), tx = vec3_create(1, 0, 0), ty = vec3_create(0, 1, 0);
    vec4 viewport = { 0, 0, width, height };

    rda = orbit_camera_unproject(t0, viewport, m4inverted);
    rdb = orbit_camera_unproject(tx, viewport, m4inverted);
    planeYPosition = orbit_camera_unproject(ty, viewport, m4inverted);
    dcol = planeYPosition - rda;
    drow = rdb - rda;

    int i=0, bh = height;
#ifdef ENABLE_THREADS
    bh = (height/TOTAL_THREADS);

    for (; i<TOTAL_THREADS; i++) {
#endif
      areas[i].dcol = dcol;
      areas[i].drow = drow;
      areas[i].pos = planeYPosition;
      areas[i].ro = ro;
      areas[i].x = 0;
      areas[i].y = i*bh;
      areas[i].width = width;
      areas[i].height = areas[i].y + (int)(bh);
      areas[i].screen_height = (int)(height);
      areas[i].stride = stride;
      areas[i].data = data;
      areas[i].render_id = i;
      areas[i].bricks = my_first_brick;
      areas[i].brick_count = brick_count;
      areas[i].scene = scene;
#ifdef ENABLE_THREADS
      thpool_add_work(thpool, (void *)render_screen_area, (void *)(&areas[i]));
    }

    thpool_wait(thpool);
#else
    render_screen_area((void *)(&areas[i]));
#endif

#ifdef RENDER
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1.0f, -1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex2f( -1, -1);
      glTexCoord2f(1.0f, 0.0f); glVertex2f(  1, -1);
      glTexCoord2f(1.0f, 1.0f); glVertex2f(  1,  1);
      glTexCoord2f(0.0f, 1.0f); glVertex2f( -1,  1);
    glEnd();

    glfwSwapBuffers(window);

    glDeleteTextures(1, &texture[0]);
#endif

    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
