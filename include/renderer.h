#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "linmath.h"

#include "shader.h"
#include "common.h"

class Renderer
{
public:
  // Constructor (inits shaders/shapes)
  Renderer(Shader &shader);
  // Destructor
  ~Renderer();
  // Renders a defined quad textured with given sprite
  void DrawSprite(Vertex vertex);

private:
  // Render state
  Shader shader;
  unsigned int quadVAO;
  GLint mvp_location;
  // Initializes and configures the quad's buffer and vertex attributes
  void initRenderData();
};

#endif