#ifndef SHADER_H
#define SHADER_H

#include <glx.h>
#include <util.h>

#include <fstream>
#include <sstream>

class Shader
{
public:
  unsigned int programID;
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();
  void use();
  void setBool(const std::string &name, bool value);
  void setInt(const std::string &name, int value);
  void setFloat(const std::string &name, float value);
};

#endif