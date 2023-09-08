

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <resource_manager.h>
#include <sprite_renderer.h>
#include <gameobject.h>
#include <tetromino.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

// Represents the current state of the game
enum GameState
{
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

static const float DELTA_L = 10.f;

    // Game holds all game-related state and functionality.
    // Combines all game-related data into a single class for
    // easy access to each of the components and manageability.
    class Game
{
private:
  SpriteRenderer *renderer;
  std::vector<GameObject> cubes, objects;
  Tetromino tetromino; 

public:
  // game state
  GameState State;
  bool Keys[1024];
  unsigned int Width, Height;
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
};

#endif
