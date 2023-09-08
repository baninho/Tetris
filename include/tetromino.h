#ifndef TETROMINO_H_
#define TETROMINO_H_

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <gameobject.h>
#include <sprite_renderer.h>
#include <resource_manager.h>

#include <string>
#include <vector>

class Tetromino 
{
private:
  std::vector<GameObject> cubes;
public:
  Tetromino();
  ~Tetromino();
  void Render(SpriteRenderer &renderer);
  void Spawn(std::string type);
  void Update(float dt);
};

#endif