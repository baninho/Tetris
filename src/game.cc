

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
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
  ResourceManager::LoadTexture("../textures/block.png", false, "block");

  this->objects.push_back(GameObject(glm::vec2(.0f, this->Height), glm::vec2(this->Width, 100.f), ResourceManager::GetTexture("background"))); // floor
  this->objects.push_back(GameObject(glm::vec2(-100.0f, .0f), glm::vec2(100.f, this->Height), ResourceManager::GetTexture("background"))); // left wall
  this->objects.push_back(GameObject(glm::vec2(this->Width, .0f), glm::vec2(100.f, this->Height), ResourceManager::GetTexture("background"))); // right wall
}

void Game::Update(float dt)
{
  this->tetromino.Update(dt);
  this->HandleCollisions();
}

void Game::ProcessInput(float dt)
{
  if (this->Keys[GLFW_KEY_SPACE] && this->State == GAME_MENU)
  {
    this->State = GAME_ACTIVE;
    this->tetromino.Spawn(TETRO_J);
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
  renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
  for (int i = 0; i < this->cubes.size(); i++)
  {
    this->cubes.at(i).Draw(*renderer);
  }
  this->tetromino.Render(*renderer);
}

void Game::HandleCollisions()
{
  bool clear_below = true;

  for (GameObject &cube : this->tetromino.get_cubes()) 
  {

    for (GameObject &other : this->objects)
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.StopX();
        clear_below = clear_below && this->CheckPathClear(cube, other);
      }
    }
    for (GameObject &other : this->cubes)
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.StopX();
        clear_below = clear_below && this->CheckPathClear(cube, other);
      }
    }

    if (!clear_below)
    {
      this->tetromino.Stop();
      std::vector<GameObject> temp = this->tetromino.get_cubes();
      for (GameObject cube : temp) 
      {
        this->cubes.push_back(cube);
      }
      this->tetromino = Tetromino((TetrominoShape)(rand() % (int)(TETRO_Z + 1)));
      return;
    } 
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
