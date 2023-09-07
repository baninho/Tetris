#ifndef TETRIS_CUBE_H_
#define TETRIS_CUBE_H_

#include "common.h"
#include <vector>

class Cube 
{
  private: 
    float x_position_, y_position_, length_;
    std::vector<Vertex> vertices_;

  public:
    Cube(float x, float y, float l);
    ~Cube();
    void MoveX(float x_offset);
    void MoveY(float y_offset);
    void UpdateVertices();
    float get_x_position();
    float get_y_position();
    float get_length();
    std::vector<Vertex> get_vertices();
};

#endif