#include <cube.h>
#include <algorithm>

Cube::Cube(float x, float y, float l)
{
  this->x_position_ = x;
  this->y_position_ = y;
  this->length_ = l;
  this->UpdateVertices();
}

Cube::~Cube()
{
}

void Cube::MoveX(float x_offset) 
{
  this->x_position_ += x_offset;
  this->UpdateVertices();
}

void Cube::MoveY(float y_offset)
{
  this->y_position_ += y_offset;
  this->UpdateVertices();
}

void Cube::UpdateVertices()
{
  Vertex temp_[4] =
      {{this->x_position_, this->y_position_, 0.f, 1.f, 0.f},
       {this->x_position_, this->y_position_ - this->length_, 1.f, 0.f, 0.f},
       {this->x_position_ + this->length_, this->y_position_, 0.f, 0.f, 1.f},
       {this->x_position_ + this->length_, this->y_position_ - this->length_, 0.f, 1.f, 0.f}};
  for (Vertex v : temp_)
  {
    this->vertices_.push_back(v);
  }
}

float Cube::get_x_position()
{
  return this->x_position_;
}

float Cube::get_y_position()
{
  return this->y_position_;
}

float Cube::get_length()
{
  return this->length_;
}

std::vector<Vertex> Cube::get_vertices()
{
  return this->vertices_;
}