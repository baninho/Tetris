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
  switch (type)
  {
  case TETRO_I:
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_PUPLE, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_GREEN, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_ORANGE, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 120.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_TEAL, TETRO_SPEED));
    break;

  case TETRO_J:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    break;

  case TETRO_L:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    break;

  case TETRO_O:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    break;

  case TETRO_S:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    break;

  case TETRO_T:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    break;

  case TETRO_Z:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED, TETRO_SPEED));
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
    this->cubes.at(i).Position.y = CUBE_SIZE.y * floor(this->cubes.at(i).Position.y / CUBE_SIZE.y); // snap to grid
  }
}
