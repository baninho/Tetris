

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <gameobject.h>

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) 
    {
    }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) 
    {
    }

void GameObject::Draw(SpriteRenderer &renderer)
{
  renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Update(float dt)
{
  if (this->Position.y >= 760.f)
  {
    this->Velocity.y = 0;
    return;
  } 
  this->Position.y += this->Velocity.y * dt;
  printf("dt: %f\nposition.y: %f\nvelocity.y: %f\n", dt, this->Position.y, this->Velocity.y);
}
