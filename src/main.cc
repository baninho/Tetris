#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>

#include <common.h>
#include <cube.h>
#include <game.h>
#include <shader.h>

static const GLfloat kxMove = .1f;
static const GLfloat kyMove = .1f;
static const GLuint kMaxCubes = 100, kNumberOfCubes = 2;
static const GLuint kVerticesPerCube = 4;
static const GLint kVposLocation = 0;
static const GLint kVcolorLocation = 1;

Cube cubes[kNumberOfCubes] = {Cube(-.05f, .05f, .06f), Cube(.01f, .05f, .06f)};
Vertex vertices2[kNumberOfCubes * kVerticesPerCube];

void updateVertexBuffer()
{
  for (int j = 0; j < kNumberOfCubes; j++)
  {
    std::vector<Vertex> temp_ = cubes[j].get_vertices();
    for (int i = 0; i < kVerticesPerCube; i++)
    {
      vertices2[i + j * kVerticesPerCube] = temp_[i];
    }
  }
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);
}

static void error_callback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (action != GLFW_PRESS) return;
  if (key == GLFW_KEY_ESCAPE)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    printf("Window closed by ESC Key\n");
  }
  if (key == GLFW_KEY_A)
  {
    printf("A press\n");
    cubes[0].MoveX(-kxMove);
  }
  if (key == GLFW_KEY_D)
  {
    printf("D press\n");
    cubes[0].MoveX(kxMove);
  }
  if (key == GLFW_KEY_W)
  {
    printf("W press\n");
    cubes[0].MoveY(kyMove);
  }
  if (key == GLFW_KEY_S)
  {
    printf("S press\n");
    cubes[0].MoveY(-kyMove);
  }

  updateVertexBuffer();
}

static void error_callback(int error, char * desc) 
{
  fprintf(stderr, "GLFW ERROR %d", error);
  fprintf(stderr, "%s", desc);
}

int main(void)
{
  GLFWwindow *window;
  GLuint vertex_buffer, vertex_shader, vertex_array, fragment_shader, program;
  GLint mvp_location, success;
  GLchar info_log[512];
  std::string vertex_path = "../shaders/vertex330.glsl";
  std::string fragment_path = "../shaders/fragment330.glsl";

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  window = glfwCreateWindow(600, 800, "Tetris", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetErrorCallback(error_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);
  glfwSwapInterval(1);

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  Shader shader(vertex_path, fragment_path);

  updateVertexBuffer();
  
  glGenBuffers(1, &vertex_buffer);
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_DYNAMIC_DRAW);

  mvp_location = glGetUniformLocation(shader.program_id, "MVP");

  glEnableVertexAttribArray(kVposLocation);
  glVertexAttribPointer(kVposLocation, 2, GL_FLOAT, GL_FALSE,
                        sizeof(vertices2[0]), (void *)0);
  glEnableVertexAttribArray(kVcolorLocation);
  glVertexAttribPointer(kVcolorLocation, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertices2[0]), (void *)(sizeof(float) * 2));

  while (!glfwWindowShouldClose(window))
  {
    float ratio;
    int width, height;
    mat4x4 m, p, mvp;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClearColor(0.8f, 0.6f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4_identity(m);
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    shader.use();
    glBindVertexArray(vertex_array);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(vertices2)/sizeof(vertices2[0]));

    glfwSwapBuffers(window);
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}