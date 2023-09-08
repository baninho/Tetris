

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
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
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
  ResourceManager::LoadTexture("../textures/awesomeface.png", true, "face");
  ResourceManager::LoadTexture("../textures/background.jpg", false, "background");
  ResourceManager::LoadTexture("../textures/birnen.jpg", false, "birnen");
  ResourceManager::LoadTexture("../textures/block.png", false, "block");

  this->tetromino.Spawn(TETRO_I);
  this->objects.push_back(GameObject(glm::vec2(.0f, this->Height), glm::vec2(this->Width, 1.f), ResourceManager::GetTexture("background")));
}

void Game::Update(float dt)
{
  this->tetromino.Update(dt);
  this->HandleCollisions();
}

void Game::ProcessInput(float dt)
{
  if (this->Keys[GLFW_KEY_S]) 
  {
    printf("S pressed\n");
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
  for (GameObject &cube : this->tetromino.get_cubes()) 
  {
    for (GameObject &other : this->objects)
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.Stop();
        break;
      }
    }
    for (GameObject &other : this->cubes)
    {
      if (this->DetectCollision(cube, other))
      {
        this->tetromino.Stop();
        break;
      }
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
