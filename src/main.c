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
  int height;
  int stride;
  int render_id;
  vec3 pos;
  vec3 dcol;
  vec3 drow;
  vec3 ro;
  vec4 color;
  voxel_brick *brick;
} screen_area;

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
  // vec3 center = aabb_center(c->bounds);
  vec3 center = c->brick->center;
  vec3 m;
  // float r = (c->bounds[1][0] - center[0]) * 0.97f;
  float r = VOXEL_BRICK_SIZE * 0.97f;
  int result;
  int x, y;

  aabb_packet bounds;
  bounds[0] = _mm_sub_ps(c->brick->bounds_packet[0], vec3f(ro[0]));
  bounds[1] = _mm_sub_ps(c->brick->bounds_packet[1], vec3f(ro[1]));
  bounds[2] = _mm_sub_ps(c->brick->bounds_packet[2], vec3f(ro[2]));
  bounds[3] = _mm_sub_ps(c->brick->bounds_packet[3], vec3f(ro[0]));
  bounds[4] = _mm_sub_ps(c->brick->bounds_packet[4], vec3f(ro[1]));
  bounds[5] = _mm_sub_ps(c->brick->bounds_packet[5], vec3f(ro[2]));

  for (y=c->y; y<height; ++y) {
    planeXPosition = planeYPosition;
    for (x=0; x<width; x+=4) {
      for (int i=0; i<4; i++) {
        planeXPosition += drow;
        rd = planeXPosition - ro;
        dir[i] = rd;
        invdir[i] = vec3_reciprocal(rd);
        packet.invdir[0][i] = invdir[i][0];
        packet.invdir[1][i] = invdir[i][1];
        packet.invdir[2][i] = invdir[i][2];
      }

      result = ray_isect_packet(packet, bounds, &m);
      for (int j=0; j<4; j++) {
        unsigned long where = y * width * stride + (x + j) * stride;

        if (result & (1<<j)) {
          o = (ro + dir[j] * vec3f(m[j])) - center;

          for (int k=0; k<3; k++) {
            if (fabsf(o[k]) >= r) {
              normal[k] = o[k] > 0.0f ? 1.0f : -1.0f;
            } else {
              normal[k] = 0.0f;
            }
          }

          float sum = fabsf(normal[0]) + fabsf(normal[1]) + fabsf(normal[2]);

          if (sum == 3) {
            data[where+0] = 140;//(int)(normal[0] * 255 + 127);
            data[where+1] = 140;//(int)(normal[1] * 255 + 127);
            data[where+2] = 140;//(int)(normal[2] * 255 + 127);
          } else if (sum == 2) {
            data[where+0] = 160;//(int)(normal[0] * 255 + 127);
            data[where+1] = 160;//(int)(normal[1] * 255 + 127);
            data[where+2] = 160;//(int)(normal[2] * 255 + 127);
          } else {
            data[where+0] = 0;//(int)(o[0] * 255 + 127);
            data[where+1] = 0;//(int)(o[1] * 255 + 127);
            data[where+2] = 0;//(int)(o[2] * 255 + 127);
          }
        } else {
          data[where+0] = 0;
          data[where+1] = 0;
          data[where+2] = 0;
        }
      }
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

  vec3 eye = vec3_create(0.0, 0.0, -1.0);
  vec3 center = vec3_create(0.0, 0.0, 0.0 );
  vec3 up = vec3_create(0.0, 1.0, 0.0 );

  orbit_camera_init(eye, center, up);

  // TODO: handle resize

  int dw, dh;
  glfwGetFramebufferSize(window, &dw, &dh);
  int stride = 3;
  int total = dw*dh*stride;
  uint8_t *data = malloc(total);

  aabb bounds = {
    {-.1, -.1, -.1},
    { .1,  .1,  .1}
  };

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
  voxel_brick my_first_brick;
  vec3 zero = vec3f(0.0f);
  voxel_brick_position(&my_first_brick, zero);
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

    for (i; i<TOTAL_THREADS; i++) {
#endif
      areas[i].dcol = dcol;
      areas[i].drow = drow;
      areas[i].pos = planeYPosition;
      areas[i].ro = ro;
      areas[i].x = 0;
      areas[i].y = i*bh;
      areas[i].width = width;
      areas[i].height = areas[i].y + (int)(bh);
      areas[i].stride = stride;
      areas[i].data = data;
      areas[i].render_id = i;
      areas[i].brick = &my_first_brick;
#ifdef ENABLE_THREADS
      thpool_add_work(thpool, (void *)render_screen_area, (void *)(&areas[i]));
    }

    thpool_wait(thpool);
#else
    render_screen_area((void *)(&areas[0]));
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
