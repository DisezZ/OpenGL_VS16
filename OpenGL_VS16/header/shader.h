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
  void setInt(const std::string& name, int value);
  void setFloat(const std::string &name, float value);
  void setVec2(const std::string& name, glm::vec2 vec);
  void setVec3(const std::string& name, glm::vec3 vec);
  void setVec4(const std::string& name, glm::vec4 vec);
  void setMat2(const std::string& name, glm::mat2 mat);
  void setMat3(const std::string& name, glm::mat3 mat);
  void setMat4(const std::string& name, glm::mat4 mat);
};

#endif