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

void Tetromino::Spawn(TetrominoShape type)
{
  switch (type) // I J L O S T Z
  {
  case TETRO_I:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 80.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 120.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_J:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_L:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_O:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_S:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_T:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  case TETRO_Z:
    /* code */
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), glm::vec3(1.0f, .0f, .0f), glm::vec2(.0f, 100.f)));
    break;

  default:
    break;
  }
}

void Tetromino::Update(float dt)
{
  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Update(dt);
    if (this->cubes.at(i).DetectCollision()) this->Stop();
  }
}

void Tetromino::Stop()
{
  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Velocity = glm::vec2(.0f, .0f);
  }
}
