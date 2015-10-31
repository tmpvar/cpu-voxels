#include <GLFW/glfw3.h>
#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aabb.h"
#include "ray-aabb.h"

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

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

void orbit_camera_lookat(vec3 eye, vec3 center, vec3 up) {
  mat4_look_at(orbit_camera.scratch0, eye, center, up);
  quat_from_mat4(orbit_camera.rotation, orbit_camera.scratch0);
  quat_norm(orbit_camera.rotation, orbit_camera.rotation);
  vec3_copy(orbit_camera.center, center);
  orbit_camera.distance = vec3_distance(eye, center);
}

void orbit_camera_init(vec3 eye, vec3 center, vec3 up) {
  quat_identity(orbit_camera.rotation);
  orbit_camera_lookat(eye, center, up);
}

void orbit_camera_rotate(float sx, float sy, float ex, float ey) {
  quat s = { sx, sy, 0.0f };
  quat e = { ex, ey, 0.0f };

  quat_invert(e, e);
  quat_mul(s, s, e);

  if(vec4_len(s) < 1e-6) {
    return;
  }

  quat_mul(orbit_camera.rotation, orbit_camera.rotation, s);
  vec4_norm(orbit_camera.rotation, orbit_camera.rotation);
}

void orbit_camera_unproject(vec3 r, vec3 vec, vec4 viewport, mat4 inv) {
  float viewX = viewport[0];
  float viewY = viewport[1];
  float viewWidth = viewport[2];
  float viewHeight = viewport[3];

  float x = vec[0];
  float y = vec[1];
  float z = vec[2];

  x = x - viewX;
  y = viewHeight - y - 1;
  y = y - viewY;

  r[0] = (2 * x) / viewWidth - 1;
  r[1] = (2 * y) / viewHeight - 1;
  r[2] = 2 * z - 1;

  vec3_transform(r, r, inv);
}

void orbit_camera_view(mat4 view) {

  // mat4_from_quat(view, orbit_camera.rotation);
  // Here's hoping that we conjegate in the above!
  quat q;
  vec3 s = { 0.0, 0.0, -orbit_camera.distance };
  quat_conj(q, orbit_camera.rotation);
  mat4_from_rotation_translation(view, q, s);
  // mat4.fromRotationTranslation(view,
  //   quat.conjugate(scratch0, this.rotation),
  //   scratch1)
  vec3_negate(orbit_camera.v3scratch, orbit_camera.center);
  mat4_translate(view, orbit_camera.v3scratch);
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
printf("here %f,%f -> %f,%f\n", mouse.x, mouse.y, x, y);
    mouse.x = x;
    mouse.y = y;


    mat4 view;
    mat4_identity(view);

    // printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
    //   view[0][0], view[1][0], view[2][0], view[3][0],
    //   view[0][1], view[1][1], view[2][1], view[3][1],
    //   view[0][2], view[1][2], view[2][2], view[3][2],
    //   view[0][3], view[1][3], view[2][3], view[3][3]
    // );



    orbit_camera_view(view);

    int a = 1;
    // printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
    //   view[0][0], view[1][0], view[2][0], view[3][0],
    //   view[0][1], view[1][1], view[2][1], view[3][1],
    //   view[0][2], view[1][2], view[2][2], view[3][2],
    //   view[0][3], view[1][3], view[2][3], view[3][3]
    // );

  }
}


int main(void)
{
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, mouse_move_callback);

  vec3 eye = { 0.0, 0.0, 0 };
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

  // memset(data, 0, total);
  for (int i=0; i<total; i+=stride) {
    data[i+0] = 0;
    data[i+1] = 255;
    data[i+2] = 0;
  }

  aabb bounds = {
    {-1, -1, -1},
    { 1,  1,  1}
  };

  vec3 ro, rd;
  mat4 m4inverted, view;

  GLuint texture[1];
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glfwGetFramebufferSize(window, &width, &height);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, dw, dh, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  mat4 projection;
  mat4_identity(projection);
  mat4_perspective(
    projection,
    M_PI/4.0,
    dw / dh,
    0.1,
    1000.0
  );

  return 0;

  while (!glfwWindowShouldClose(window)) {
    glfwGetFramebufferSize(window, &width, &height);


    orbit_camera_view(view);
    mat4_get_eye(ro, view);

    mat4_mul(m4inverted, projection, view);
    mat4_invert(m4inverted, m4inverted);

    // compute 3 points so that we can interpolate instead of unprojecting
    // on every point
    vec3 rda, rdb, planeYPosition, dcol, drow, p;
    vec3 t0 = {0, 0, 0}, tx = {1, 0, 0}, ty = {0, 1, 0};
    vec4 viewport = { 0, 0, width, height };
    orbit_camera_unproject(rda, t0, viewport, m4inverted);
    orbit_camera_unproject(rda, tx, viewport, m4inverted);
    orbit_camera_unproject(planeYPosition, ty, viewport, m4inverted);

    vec3_sub(dcol, planeYPosition, rda);
    vec3_sub(dcol, rdb, rda);




    float aspect = width / (float) height;
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

    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex2f( -1, -1);
      glTexCoord2f(1.0f, 0.0f); glVertex2f(  1, -1);
      glTexCoord2f(1.0f, 1.0f); glVertex2f(  1,  1);
      glTexCoord2f(0.0f, 1.0f); glVertex2f( -1,  1);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
