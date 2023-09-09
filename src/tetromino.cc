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

#include <tetromino.h>

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(TetrominoShape shape) : shape(shape)
{
  this->Spawn(shape);
}

Tetromino::~Tetromino()
{
}

void Tetromino::Render(SpriteRenderer &renderer)
{
  for (GameObject &cube : this->cubes)
  {
    cube.Draw(renderer);
  }
}

void Tetromino::Spawn(TetrominoShape shape)
{
  switch (shape)
  {
  case TETRO_I:
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_TEAL));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_TEAL));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_TEAL));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 120.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_TEAL));
    break;

  case TETRO_J:
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_BLUE));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_BLUE));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_BLUE));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_BLUE));
    break;

  case TETRO_L:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_ORANGE));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_ORANGE));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_ORANGE));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 80.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_ORANGE));
    break;

  case TETRO_O:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_YELLOW));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_YELLOW));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_YELLOW));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_YELLOW));
    break;

  case TETRO_S:
    this->cubes.push_back(GameObject(glm::vec2(320.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_GREEN));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_GREEN));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_GREEN));
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_GREEN));
    break;

  case TETRO_T:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_PUPLE));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_PUPLE));
    this->cubes.push_back(GameObject(glm::vec2(320.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_PUPLE));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_PUPLE));
    break;

  case TETRO_Z:
    this->cubes.push_back(GameObject(glm::vec2(240.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 0.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED));
    this->cubes.push_back(GameObject(glm::vec2(280.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED));
    this->cubes.push_back(GameObject(glm::vec2(320.0f, 40.0f), CUBE_SIZE, ResourceManager::GetTexture("block"), COLOR_RED));
    break;

  default:
    break;
  }
}

std::vector<GameObject> &Tetromino::get_cubes()
{
  return this->cubes;
}

glm::vec2 Tetromino::get_velocity()
{
  return this->velocity;
}

void Tetromino::Left()
{
this->left = true;
}

void Tetromino::Right()
{
this->right = true;
}

void Tetromino::Down()
{
  this->down = true;
}

void Tetromino::Rotate()
{
  float x = cubes.at(1).Position.x;
  float y = cubes.at(1).Position.y;

  glm::mat4 m = glm::mat4(1.0f);

  m = glm::translate(m, glm::vec3(x, y, .0f));
  m = glm::rotate(m, glm::radians(90.f), glm::vec3(0.0f, 0.0f, 1.0f));
  m = glm::translate(m, glm::vec3(-x, -y, .0f));

  for (GameObject &cube : this->cubes)
  {
    cube.Position = m * glm::vec4(cube.Position, .0f, 1.f);
  }
}

void Tetromino::SnapToGrid()
{
  for (GameObject &cube : this->cubes)
  {
    cube.Position = CUBE_SIZE * round(cube.Position / CUBE_SIZE);
  }
}

void Tetromino::Update(float dt)
{
  if (this->stopped)
    return;

  if (this->left)
  {
    this->velocity.x -= TETRO_ACCELERATION * dt;
  }
  else if (this->velocity.x < -10.f)
  {
    this->velocity.x += TETRO_DECELERATION * dt;
  }

  if (this->right)
  {
    this->velocity.x += TETRO_ACCELERATION * dt;
  }
  else if (this->velocity.x > 10.f)
  {
    this->velocity.x -= TETRO_DECELERATION * dt;
  }

  if (!this->left && !this->right && abs(this->velocity.x) > 0)
    this->velocity.x = 0;

  if (this->down)
  {
    this->velocity.y += TETRO_ACCELERATION * dt;
  }
  else if (this->velocity.y > 100.f || this->velocity.y < 100.f)
  {
    this->velocity.y = 100.f;
  }

  // limit speed to prevent clipping
  this->velocity = glm::min(this->velocity, glm::vec2(TETRO_MAX_SPEED));
  this->velocity = glm::max(this->velocity, glm::vec2(-TETRO_MAX_SPEED));

  for (GameObject &cube : this->cubes)
  {
    cube.Position += this->velocity * dt;
  }

  this->left = false;
  this->right = false;
  this->down = false;
}

void Tetromino::Stop()
{
  this->stopped = true;
  this->SnapToGrid();
}

void Tetromino::StopX()
{
  this->velocity.x = .0f;

  for (GameObject &cube : this->cubes)
  {
    // x snap to grid
    cube.Position.x = CUBE_SIZE.x * round(cube.Position.x / CUBE_SIZE.x);
  }
}

void Tetromino::Continue()
{
  this->stopped = false;
}
