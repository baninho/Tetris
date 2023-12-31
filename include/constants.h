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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

static const glm::vec2 CUBE_SIZE = glm::vec2(40.0f, 40.0f);
static const glm::vec3 COLOR_RED = glm::vec3(1.0f, .0f, .0f);
static const glm::vec3 COLOR_PUPLE = glm::vec3(1.0f, .0f, 1.0f);
static const glm::vec3 COLOR_GREEN = glm::vec3(0.0f, 1.0f, .0f);
static const glm::vec3 COLOR_YELLOW = glm::vec3(1.0f, 1.0f, .0f);
static const glm::vec3 COLOR_ORANGE = glm::vec3(1.0f, .7f, .0f);
static const glm::vec3 COLOR_BLUE = glm::vec3(.0f, .0f, 1.0f);
static const glm::vec3 COLOR_TEAL = glm::vec3(.0f, 1.0f, 1.0f);
static const glm::vec2 TETRO_SPEED = glm::vec2(.0f, 100.f);
static const float TETRO_ACCELERATION = 900.f;
static const float TETRO_DECELERATION = 1800.f;
static const float TETRO_MAX_SPEED = 600.f;
static const float DELTA_L = 10.f;
static const int MAX_CUBE_ROWS = 20;
static const int MAX_CUBE_COLUMNS = 15;
static const int FRAME_DELAY = 3;
static const unsigned int SCREEN_WIDTH = 600;
static const unsigned int SCREEN_HEIGHT = 800;

#endif