#pragma once

#include <GLFW/glfw3.h>

#include "forward_declarations.h"

class GameWindow {
public:

private:
	GLFWwindow* window;
	AbstractServer* server;
};

