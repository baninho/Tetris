#include <tetromino.h>

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

void Tetromino::Render(SpriteRenderer &renderer)
{
  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Draw(renderer);
  }
}

void Tetromino::Spawn(std::string type)
{
  this->cubes.push_back(GameObject(glm::vec2(100.0f, 100.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
  this->cubes.push_back(GameObject(glm::vec2(100.0f, 140.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
  this->cubes.push_back(GameObject(glm::vec2(140.0f, 100.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
  this->cubes.push_back(GameObject(glm::vec2(140.0f, 140.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
}

void Tetromino::Update(float dt)
{
  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Update(dt);
  }
}
