#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "forward_declarations.h"

class GameWindow {
public:
	GameWindow(GLFWwindow* w);

private:
	GLFWwindow* window;
	AbstractServer* server;

	void gameLoop(void);
	void processKeyboardInput(void);

	//debug
	bool mouseButtonLeftDown;
};

