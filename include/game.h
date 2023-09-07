#ifndef GAME_H
#define GAME_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// Represents the current state of the game
enum GameState
{
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game
{
private:
  unsigned int width_, height_;
public:
  // game state
  GameState State;
  bool Keys[1024];
  // constructor/destructor
  Game(unsigned int width, unsigned int height);
  ~Game();
  // initialize game state (load all shaders/textures/levels)
  void Init();
  // game loop
  void ProcessInput(float dt);
  void Update(float dt);
  void Render();
};

#endif