#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <glx.h>
#include <util.h>
#include <camera.h>

// default window values
const int WND_WIDTH = 1280;
const int WND_HEIGHT = 720;

class Window
{
public:
	GLFWwindow* window = nullptr;
	GLFWmonitor* monitor = nullptr;
	Camera camera;
	Window();
	~Window();
	int Create();
	void Destroy();
	void mainLoop();
	void process_input();
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

private:
	float lastX = WND_WIDTH/2;
	float lastY = WND_HEIGHT/2;
	bool firstMouse = true;
	float lastFrame = 0.0f; // Time of last frame
	glm::ivec2 wndPos = glm::ivec2(0);
	glm::ivec2 wndSize = glm::ivec2(WND_WIDTH, WND_HEIGHT);
};

#endif // !WINDOW_H
