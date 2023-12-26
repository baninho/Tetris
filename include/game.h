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

#ifndef GAME_H
#define GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <stdlib.h>

#include <resource_manager.h>
#include <sprite_renderer.h>
#include <gameobject.h>
#include <tetromino.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "constants.h"
#include "text_renderer.h"

// Represents the current state of the game
enum GameState
{
  GAME_MENU,
  GAME_ACTIVE,
  GAME_OVER
};

    // Game holds all game-related state and functionality.
    // Combines all game-related data into a single class for
    // easy access to each of the components and manageability.
    class Game
{
private:
  SpriteRenderer *renderer;
  std::vector<GameObject> cubes, objects;
  Tetromino tetromino, next_tetro;
  TextRenderer *text;
  int score, rows_completed_at_once;
  bool soft_drop;
  TetrominoShape next_shape;

public:
  // game state
  GameState State;
  bool Keys[1024];
  unsigned int Width, Height;
  static std::vector<int> CompletedRows;
  // constructor/destructor
  Game(unsigned int width, unsigned int height);
  ~Game();
  // initialize game state (load all shaders/textures/levels)
  void Init();
  // game loop
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
  void HandleCollisions();
  bool DetectCollision(GameObject object, GameObject other);
  bool CheckPathClear(GameObject object, GameObject other);
  static bool CubeInCompletedRow(GameObject &cube);
  void CheckRowsForCompletion();
  void ClearCompletedRows();
  bool CheckClearLeft(GameObject object, GameObject other);
  bool CheckClearRight(GameObject object, GameObject other);
  bool CheckTetroClearLeftChanged();
  bool CheckTetroClearRightChanged();
  void UpdateScore();
  void UpdateNextTetro();
  TetrominoShape RandomShape();
};

#endif
