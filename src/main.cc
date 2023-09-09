

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <game.h>
#include <resource_manager.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "constants.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

Game Tetris(SCREEN_WIDTH, SCREEN_HEIGHT);
int actual_width, actual_height;

int main(int argc, char *argv[])
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, false);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris!", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGL(glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwGetFramebufferSize(window, &actual_width, &actual_height);

  // OpenGL configuration
  // --------------------
  glViewport(0, 0, actual_width, actual_height);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // initialize game
  // ---------------
  Tetris.Init();

  // deltaTime variables
  // -------------------
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window))
  {
    // calculate delta time
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    // manage user input
    // -----------------
    Tetris.ProcessInput(deltaTime);

    // update game state
    // -----------------
    Tetris.Update(deltaTime);

    // render
    // ------
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Tetris.Render();

    glfwSwapBuffers(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
  }

  // delete all resources as loaded using the resource manager
  // ---------------------------------------------------------
  ResourceManager::Clear();

  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
      Tetris.Keys[key] = true;
    else if (action == GLFW_RELEASE)
      Tetris.Keys[key] = false;
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
