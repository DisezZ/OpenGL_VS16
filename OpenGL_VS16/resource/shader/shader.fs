#version 330 core
out vec4 fragColor;
in vec3 ourNormal;
in vec2 ourTexCoord;
uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
void main()
{
  fragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f);
}