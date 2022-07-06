#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "forward_declarations.h"

class GameWindow {
public:
	GameWindow(GLFWwindow* w);
	GameWindow(GLFWwindow* w, int timeSeconds, int numAnts);

private:

	const double FPS_LIMIT;

	GLFWwindow* window;
	AbstractServer* server;

	void gameLoop(void);
	void processKeyboardInput(void);

	//debug
	int timeSeconds;
	int numAnts;
	double approxdT;
	bool mouseButtonLeftDown;
};

