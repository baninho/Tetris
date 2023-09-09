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

#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <gameobject.h>
#include <sprite_renderer.h>
#include <resource_manager.h>

#include <string>
#include <vector>

#include "../glm/glm.hpp"
#include "constants.h"

enum TetrominoShape
{
  TETRO_I,
  TETRO_J,
  TETRO_L,
  TETRO_O,
  TETRO_S,
  TETRO_T,
  TETRO_Z
};

class Tetromino 
{
private:
  std::vector<GameObject> cubes;
  bool left, right, down, stopped;
  glm::vec2 velocity;
  TetrominoShape shape;

public:
  Tetromino();
  Tetromino(TetrominoShape shape);
  ~Tetromino();
  void Render(SpriteRenderer &renderer);
  void Update(float dt);
  void Stop();
  void StopX();
  void Continue();
  void Spawn(TetrominoShape shape);
  std::vector<GameObject> &get_cubes();
  glm::vec2 get_velocity();
  void Left();
  void Right();
  void Down();
  void Rotate();
  void SnapToGrid();
  void MoveToNextTetroPosition();
};

#endif