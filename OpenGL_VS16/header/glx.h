#pragma once
#ifndef GLX_H
#define GLX_H

#include <stdio.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

void glxSetup();
void glxTerminate();

#endif