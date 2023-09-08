cmake_minimum_required(VERSION 3.10)
project(Tetris VERSION 0.1)
add_executable(Tetris 
  src/main.cc 
  src/game.cc 
  src/shader.cc 
  src/texture.cc 
  src/resource_manager.cc 
  src/sprite_renderer.cc 
  src/gameobject.cc
  src/tetromino.cc
)
add_library(glad glad/src/gl.c)
include_directories(~/Projects/Tetris/glad/include glfw-3.3.8/deps include ~/Projects/Tetris/glm)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.8)
target_link_libraries(Tetris glfw glad)