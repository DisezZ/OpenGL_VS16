#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
out vec3 ourNormal;
out vec2 ourTexCoord;
out vec3 fragPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 transform;
void main()
{
  gl_Position = projection * view * model * transform * vec4(aPos, 1.0f);
  ourNormal = mat3(transpose(inverse(model))) * aNormal;
  ourTexCoord = aTexCoord;
  fragPos = vec3(model * transform * vec4(aPos, 1.0f));
}