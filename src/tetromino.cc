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

std::vector<GameObject> Tetromino::get_cubes()
{
  return this->cubes;
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

  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Stopped = true;
    this->cubes.at(i).Velocity = glm::vec2(.0f, .0f);
    // snap to grid
    this->cubes.at(i).Position = CUBE_SIZE * round(this->cubes.at(i).Position / CUBE_SIZE); 
  }
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
