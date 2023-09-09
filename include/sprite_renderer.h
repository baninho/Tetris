/*******************************************************************
**
** Licensed under the terms of the CC BY-NC 4.0 license as published by
** Creative Commons. You can find a human-readable format of the license
** here: https://creativecommons.org/licenses/by-nc/4.0/ and the full
** license here: https://creativecommons.org/licenses/by-nc/4.0/legalcode
**
** Based on the code for Breakout as published by
** Joey de Vries (https://github.com/joeyDeVries/)
**
** Author: Florian Imbt (https://github.com/baninho)
**
******************************************************************/

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/gl.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:
  // Constructor (inits shaders/shapes)
  SpriteRenderer(Shader shader);
  // Destructor
  ~SpriteRenderer();
  // Renders a defined quad textured with given sprite
  void DrawSprite(Texture2D texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
  // Render state
  Shader shader;
  unsigned int quadVAO;
  // Initializes and configures the quad's buffer and vertex attributes
  void initRenderData();
};

#endif
