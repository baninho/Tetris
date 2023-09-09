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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/gl.h>
#include "../glm/glm.hpp"

#include "texture.h"
#include "sprite_renderer.h"
#include "constants.h"

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
  // object state
  glm::vec2 Position, Size;
  glm::vec3 Color;
  float Rotation;
  int Row;
  bool CompletedRow;
  // render state
  Texture2D Sprite;
  // constructor(s)
  GameObject();
  GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
  // draw sprite
  virtual void Draw(SpriteRenderer &renderer);
};

#endif
