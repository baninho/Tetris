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
  src/text_renderer.cc
)
add_library(glad glad/src/gl.c)
include_directories(glad/include glfw-3.3.8/deps include glm /usr/local/include /usr/local/include/freetype2)
set_property(TARGET Tetris PROPERTY CXX_STANDARD 20)
set_property(TARGET Tetris PROPERTY CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.8)
find_package(FREETYPE REQUIRED)
target_link_libraries(Tetris 
  glfw 
  glad 
  ${FREETYPE_LIBRARY} 
)