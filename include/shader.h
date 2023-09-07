#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
  // utility function for checking shader compilation/linking errors.
  // ------------------------------------------------------------------------
  void checkCompileErrors(unsigned int shader, std::string type);

public:
  // the program ID
  unsigned int program_id;

  // constructor reads and builds the shader
  Shader(std::string vertexPath, std::string fragmentPath);
  // use/activate the shader
  void use();
  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

#endif