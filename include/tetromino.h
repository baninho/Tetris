#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <gameobject.h>
#include <sprite_renderer.h>
#include <resource_manager.h>

#include <string>
#include <vector>

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
public:
  Tetromino();
  ~Tetromino();
  void Render(SpriteRenderer &renderer);
  void Update(float dt);
  void Stop();
  void Spawn(TetrominoShape type);
};

#endif