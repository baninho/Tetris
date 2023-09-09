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

#include <gameobject.h>

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Sprite(), Row(MAX_CUBE_ROWS), CompletedRow(false)
    {
    }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
    : Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite), Row(MAX_CUBE_ROWS), CompletedRow(false)
    {
    }

void GameObject::Draw(SpriteRenderer &renderer)
{
  renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}