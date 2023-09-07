#include <renderer.h>

Renderer::Renderer(Shader &shader)
{
  this->shader = shader;
  this->mvp_location = glGetUniformLocation(shader.program_id, "MVP");
}

Renderer::~Renderer()
{
}

void Renderer::DrawSprite(Vertex vertex)
{
  float ratio;
  int width = 600, height = 800;
  mat4x4 m, p, mvp;

  this->shader.Use();

  ratio = width / (float)height;

  mat4x4_identity(m);
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);
  mat4x4_translate_in_place(mvp, vertex.x, vertex.y, .0f);
  mat4x4_scale(mvp, mvp, .06f);

  glViewport(0, 0, width, height);
  glClearColor(0.8f, 0.6f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUniformMatrix4fv(this->mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void Renderer::initRenderData()
{
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
      // pos      // color
      0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

      0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.0f, 0.0f};

  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(kVposLocation);
  glVertexAttribPointer(kVposLocation, 2, GL_FLOAT, GL_FALSE,
                        5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(kVcolorLocation);
  glVertexAttribPointer(kVcolorLocation, 3, GL_FLOAT, GL_FALSE,
                        5 * sizeof(float), (void *)(sizeof(float) * 2));
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}