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

static const glm::vec2 CUBE_SIZE = glm::vec2(40.0f, 40.0f);
static const glm::vec3 COLOR_RED = glm::vec3(1.0f, .0f, .0f);
static const glm::vec3 COLOR_PUPLE = glm::vec3(1.0f, .0f, 1.0f);
static const glm::vec3 COLOR_GREEN = glm::vec3(0.0f, 1.0f, .0f);
static const glm::vec3 COLOR_YELLOW = glm::vec3(1.0f, 1.0f, .0f);
static const glm::vec3 COLOR_ORANGE = glm::vec3(1.0f, .7f, .0f);
static const glm::vec3 COLOR_BLUE = glm::vec3(.0f, .0f, 1.0f);
static const glm::vec3 COLOR_TEAL = glm::vec3(.0f, 1.0f, 1.0f);
static const glm::vec2 TETRO_SPEED = glm::vec2(.0f, 100.f);
static const float TETRO_ACCELERATION = 900.f;
static const float TETRO_DECELERATION = 1800.f;
static const float TETRO_MAX_SPEED = 450.f;

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

public:
  Tetromino();
  ~Tetromino();
  void Render(SpriteRenderer &renderer);
  void Update(float dt);
  void Stop();
  void StopX();
  void Spawn(TetrominoShape type);
  std::vector<GameObject> get_cubes();
  void Left();
  void Right();
  void Down();
};

#endif