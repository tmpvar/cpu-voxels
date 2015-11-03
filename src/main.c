#include <GLFW/glfw3.h>
#include <3d.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aabb.h"
#include "ray.h"
#include "ray-aabb.h"

struct {
  uint8_t down;
  double x, y;
} mouse;

struct {
  quat rotation;
  vec3 center, v3scratch;
  double distance;
  mat4 scratch0, scratch1;
} orbit_camera;

static void orbit_camera_lookat(const vec3 eye, const vec3 center, const vec3 up) {
  mat4_look_at(orbit_camera.scratch0, eye, center, up);
  quat_from_mat4(orbit_camera.rotation, orbit_camera.scratch0);
  quat_norm(orbit_camera.rotation, orbit_camera.rotation);
  vec3_copy(orbit_camera.center, center);
  orbit_camera.distance = vec3_distance(eye, center);
}

static void orbit_camera_init(const vec3 eye, const vec3 center, const vec3 up) {
  quat_identity(orbit_camera.rotation);
  orbit_camera_lookat(eye, center, up);
}

static void orbit_camera_rotate(const double sx, const double sy, const double ex, const double ey) {
  const vec3 vs = { sx, sy, 0.0f };
  const vec3 ve = { ex, ey, 0.0f };
  quat s, e;

  quat_from_vec3(s, vs);
  quat_from_vec3(e, ve);

  quat_invert(e, e);
  quat_mul(s, s, e);

  if(vec4_len(s) < 1e-6) {
    printf("MISS %f\n", vec4_len(s));
    return;
  }

  quat_mul(orbit_camera.rotation, orbit_camera.rotation, s);
  quat_norm(orbit_camera.rotation, orbit_camera.rotation);
}

static void orbit_camera_unproject(vec3 r, const vec3 vec, const vec4 viewport, const mat4 inv) {
  double viewX = viewport[0];
  double viewY = viewport[1];
  double viewWidth = viewport[2];
  double viewHeight = viewport[3];

  double x = vec[0];
  double y = vec[1];
  double z = vec[2];

  x = x - viewX;
  y = viewHeight - y - 1;
  y = y - viewY;

  r[0] = (2 * x) / viewWidth - 1;
  r[1] = (2 * y) / viewHeight - 1;
  r[2] = 2 * z - 1;

  vec3_transform(r, r, inv);
}

static void orbit_camera_view(const mat4 view) {
  quat q;
  vec3 s = { 0.0, 0.0, -orbit_camera.distance };
  quat_conj(q, orbit_camera.rotation);
  mat4_from_rotation_translation(view, q, s);
  vec3_negate(orbit_camera.v3scratch, orbit_camera.center);
  mat4_translate(view, orbit_camera.v3scratch);
}

static void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    switch (key) {
      case GLFW_KEY_LEFT:
        orbit_camera_rotate(0, 0, -.1, 0);
      break;

      case GLFW_KEY_RIGHT:
        orbit_camera_rotate(0, 0, .1, 0);
      break;

      case GLFW_KEY_UP:
        orbit_camera_rotate(0, 0, 0, -.1);
      break;

      case GLFW_KEY_DOWN:
        orbit_camera_rotate(0, 0, 0, .1);
      break;

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

    orbit_camera_rotate(
      mouse.x / w - 0.5,
      mouse.y / h - 0.5,
      x / w - 0.5,
      y / h - 0.5
    );

    printf("here (%f, %f) -> (%f, %f)\n", mouse.x / w - 0.5,  mouse.y / h - 0.5, x/w-.5, y/h-.5);
  }

  mouse.x = x;
  mouse.y = y;
}

void vec3_print(vec3 v) {
  printf("(%f, %f, %f)\n", v[0], v[1], v[2]);
}

int main(void)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, mouse_move_callback);
  glfwSetKeyCallback(window, key_callback);

  vec3 eye = { 0.0, 0.0, -10 };
  vec3 center = { 0.0, 0.0, 0.0 };
  vec3 up = { 0.0, 1.0, 0.0 };

  orbit_camera_init(eye, center, up);

  int width, height;

  // TODO: handle resize

  int dw, dh;
  glfwGetFramebufferSize(window, &dw, &dh);
  int stride = 3;
  int total = dw*dh*stride;
  uint8_t *data = malloc(total);

  aabb bounds = {
    {-1, -1, -1},
    { 1,  1,  1}
  };

  vec3 ro, rd;
  mat4 m4inverted, view;

  GLuint texture[1];

  mat4 projection;
  mat4_identity(projection);
  mat4_perspective(
    projection,
    M_PI/4.0,
    dw / dh,
    0.1,
    1000.0
  );

  glGenTextures(1, texture);
  double start = glfwGetTime();
  int fps = 0;
  unsigned long pixels = 0;
  while (!glfwWindowShouldClose(window)) {
    double now = glfwGetTime();
    if (now - start > 1) {
      printf("fps: %i (%f Mrays/s)\n", fps, pixels/1000000.0f);
      start = now;
      fps = 0;
      pixels = 0;
    }
    fps++;
    glfwGetFramebufferSize(window, &width, &height);

    orbit_camera_view(view);
    mat4_get_eye(ro, view);

    mat4_mul(m4inverted, projection, view);
    mat4_invert(m4inverted, m4inverted);

    // compute 3 points so that we can interpolate instead of unprojecting
    // on every point
    vec3 rda, rdb, planeYPosition, dcol, drow;
    vec3 planeXPosition = {0, 0, 0};
    vec3 t0 = {0, 0, 0}, tx = {1, 0, 0}, ty = {0, 1, 0};
    vec4 viewport = { 0, 0, width, height };

    ray3 ray;
    double t = 0;

    orbit_camera_unproject(rda, t0, viewport, m4inverted);
    orbit_camera_unproject(rdb, tx, viewport, m4inverted);
    orbit_camera_unproject(planeYPosition, ty, viewport, m4inverted);

    vec3_sub(dcol, planeYPosition, rda);
    vec3_sub(drow, rdb, rda);

    vec3 normal;
    unsigned hits = 0;
    double x, y;
    for (y=0; y<height; ++y) {
      vec3_add(planeYPosition, planeYPosition, dcol);
      vec3_copy(planeXPosition, planeYPosition);

      for (x=0; x<width; ++x) {
        pixels++;
        vec3_add(planeXPosition, planeXPosition, drow);

        vec3_sub(rd, planeXPosition, ro);

        unsigned long where = y * width * stride + x * stride;
        uint8_t isect;

        ray_update(&ray, ro, rd);
        isect = ray_isect(&ray, ro, rd, bounds);
        if (isect) {
       // vec3_norm(rd, rd);
          t = ray_aabb_lerp(&ray, ro, bounds, normal);


          data[where+0] = (int)(normal[0] * 127 + 127);
          data[where+1] = (int)(normal[1] * 127 + 127);
          data[where+2] = (int)(normal[2] * 127 + 127);
        } else {
          data[where+0] = 0;
          data[where+1] = 0;
          data[where+2] = 0;
        }
      }
    }

    // printf("hits: %u; total: %u\n", hits, width*height);


    double aspect = width / (double) height;
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

    // glDeleteTextures(1, &texture[0]);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
