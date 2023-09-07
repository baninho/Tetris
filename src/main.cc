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

static const GLfloat kxMove = .1f;
static const GLfloat kyMove = .1f;
static const GLuint kMaxCubes = 100;
static const GLuint kVerticesPerCube = 4;

static const char *vertex_shader_text =
    "#version 110\n"
    "uniform mat4 MVP;\n"
    "attribute vec3 vCol;\n"
    "attribute vec2 vPos;\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

static const char *fragment_shader_text =
    "#version 110\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";

static Cube cubes[2] = {Cube(-.05f, .05f, .06f), Cube(.01f, .05f, .06f)};
static GLint move_x = 0;
static GLint move_y = 0;

static void error_callback(int error, const char *description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    (void)printf("Window closed by ESC Key\n");
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS)
  {
    (void)printf("A press\n");
    move_x--;
  }
  if (key == GLFW_KEY_D && action == GLFW_PRESS)
  {
    (void)printf("D press\n");
    move_x++;
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS)
  {
    (void)printf("W press\n");
    move_y++;
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS)
  {
    (void)printf("S press\n");
    move_y--;
  }
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
  GLint mvp_location, vpos_location, vcol_location;
  Vertex vertices2[8];

  printf("vertices2[0].x: %f \n", vertices2[0].x);

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(600, 1200, "Tetris", NULL, NULL);
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

  // NOTE: OpenGL error checks have been omitted for brevity
  
  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  for (int j = 0; j < 2; j++) 
  {
    std::vector<Vertex> temp_ = cubes[j].get_vertices();
    for (int i = 0; i < kVerticesPerCube; i++)
    {
      vertices2[i + j * kVerticesPerCube] = temp_[i];
    }
  }
  
  glGenBuffers(1, &vertex_buffer);
  //glGenVertexArrays(1, &vertex_array);
  //glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  glCompileShader(fragment_shader);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  mvp_location = glGetUniformLocation(program, "MVP");
  vpos_location = glGetAttribLocation(program, "vPos");
  vcol_location = glGetAttribLocation(program, "vCol");

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                        sizeof(vertices2[0]), (void *)0);
  glEnableVertexAttribArray(vcol_location);
  glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
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
    mat4x4_translate_in_place(mvp, move_x*kxMove, move_y*kyMove, .0f);

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

    glfwSwapBuffers(window);
    glfwPollEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}