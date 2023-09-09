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

#include <game.h>

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_MENU), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
}

void Game::Init()
{
  // load shaders
  ResourceManager::LoadShader("../shaders/vertex330.glsl", "../shaders/fragment330.glsl", nullptr, "sprite");
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                    static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
  // set render-specific controls
  renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
  // load textures
  ResourceManager::LoadTexture("../textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("../textures/menu.jpg", false, "menu");
  ResourceManager::LoadTexture("../textures/block.png", false, "block");

  this->text = new TextRenderer(this->Width, this->Height);
  this->text->Load("../fonts/ocraext.TTF", 24);

  this->objects.push_back(GameObject(glm::vec2(.0f, this->Height), glm::vec2(this->Width, 100.f), ResourceManager::GetTexture("background"))); // floor
  this->objects.push_back(GameObject(glm::vec2(-100.0f, .0f), glm::vec2(100.f, this->Height), ResourceManager::GetTexture("background"))); // left wall
  this->objects.push_back(GameObject(glm::vec2(this->Width, .0f), glm::vec2(100.f, this->Height), ResourceManager::GetTexture("background"))); // right wall

  this->score = 0;
  this->rows_completed_at_once = 0;
}

void Game::Update(float dt)
{
  if (this->State == GAME_OVER)
  {
    this->State = GAME_MENU;
    this->cubes.clear();
    this->score = 0;
    return;
  }

  if (this->State == GAME_MENU)
  {
    return;
  }

  this->tetromino.Update(dt);
  this->HandleCollisions();
}

void Game::ProcessInput(float dt)
{
  if (this->Keys[GLFW_KEY_SPACE] && this->State == GAME_MENU)
  {
    this->State = GAME_ACTIVE;
    this->tetromino = Tetromino(this->RandomShape());
  }
  if (this->Keys[GLFW_KEY_S]) 
  {
    this->tetromino.Down();
  }
  if (this->Keys[GLFW_KEY_A])
  {
    this->tetromino.Left();
  }
  if (this->Keys[GLFW_KEY_D])
  {
    this->tetromino.Right();
  }
  if (this->Keys[GLFW_KEY_W])
  {
    this->Keys[GLFW_KEY_W] = false;
    this->tetromino.Rotate();
  }
}

void Game::Render()
{ 
  std::stringstream stream;

  if (this->State != GAME_ACTIVE) 
  {
    renderer->DrawSprite(ResourceManager::GetTexture("menu"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
    return;
  }

  renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

  for (GameObject &cube : this->cubes)
  {
    cube.Draw(*renderer);
  }

  stream << "Score: " << this->score;
  
  this->tetromino.Render(*renderer);
  this->text->RenderText(stream.str(), 5.f, 5.f, 1.f);
}

void Game::HandleCollisions()
{
  bool clear_below = true;

  for (GameObject &cube : this->tetromino.get_cubes()) 
  {

    for (GameObject &other : this->objects) // check wall collision
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.StopX();
        clear_below = clear_below && this->CheckPathClear(cube, other);
      }
    }
    for (GameObject &other : this->cubes) // check the stack for collision
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.StopX();
        clear_below = clear_below && this->CheckPathClear(cube, other);
      }
    }
  }

  if (!clear_below)
  {
    this->soft_drop = this->tetromino.get_velocity().y > TETRO_MAX_SPEED / 2.f;
    this->tetromino.Stop();

    for (GameObject &cube : this->tetromino.get_cubes())
    {
      if (cube.Position.y < DELTA_L) // new tetromino immediately collided with stack
      {
        this->State = GAME_OVER;
        return;
      }

      cube.Row = round(cube.Position.y / CUBE_SIZE.y);
      this->cubes.push_back(cube);
    }

    this->CheckRowsForCompletion();
    this->ClearCompletedRows();
    this->UpdateScore();

    this->tetromino = Tetromino(this->RandomShape());
    return;
  }
  else
  {
    this->tetromino.Continue();
  }
}

bool Game::DetectCollision(GameObject object, GameObject other)
{
  // collision x-axis?
  bool collisionX = object.Position.x + object.Size.x >= other.Position.x &&
                    other.Position.x + other.Size.x >= object.Position.x;
  // collision y-axis?
  bool collisionY = object.Position.y + object.Size.y >= other.Position.y &&
                    other.Position.y + other.Size.y >= object.Position.y;
  // collision only if on both axes
  return collisionX && collisionY;
}

bool Game::CheckPathClear(GameObject object, GameObject other)
{
  bool clear_below = true;

  if (object.Position.x >= other.Position.x)
    clear_below = clear_below && object.Position.x - other.Position.x > other.Size.x - DELTA_L;
  if (object.Position.x < other.Position.x)
    clear_below = clear_below && other.Position.x - object.Position.x > object.Size.x - DELTA_L;
  return clear_below;
}

bool Game::CubeInCompletedRow(GameObject &cube)
{
  return cube.CompletedRow;
}

// the idea is to simply count the cubes in every row 
// then check if any rows had all columns filled
// and mark the cubes in that row for clearing
// and slide the other rows down
void Game::CheckRowsForCompletion()
{
  int count[MAX_CUBE_ROWS] =
      {
          0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0,
          0, 0, 0, 0};

  for (GameObject &cube : this->cubes)
  {
    count[cube.Row]++;
  }

  for (int i = 0; i < MAX_CUBE_ROWS; i++)
  {
    if (count[i] >= MAX_CUBE_COLUMNS) // detected a completed row
    {
      for (GameObject &cube : this->cubes)
      {
        // mark cubes in the row for clearing
        if (cube.Row == i)
        {
          cube.CompletedRow = true;
        }          
        // slide the rows above the completed line down
        if (cube.Row < i) 
        {
          cube.Row++;
          cube.Position.y += CUBE_SIZE.y;
        }
      }

      this->rows_completed_at_once++;
    }
  }
}

void Game::ClearCompletedRows()
{
  std::erase_if(this->cubes, Game::CubeInCompletedRow);
}

void Game::UpdateScore()
{
  this->score = this->score + MAX_CUBE_COLUMNS * this->rows_completed_at_once * this->rows_completed_at_once;
  this->rows_completed_at_once = 0;
  if (this->soft_drop)
  {
    this->score++;
    this->soft_drop = false;
  }
}

TetrominoShape Game::RandomShape()
{
  return (TetrominoShape)(rand() % (int)(TETRO_Z + 1));
}