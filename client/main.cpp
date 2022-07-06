#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "forward_declarations.h"
#include "globals.h"
#include "GameWindow.h"

#include <vector>
#include <string>

GLFWwindow* setup_glfw_window(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Command Ant Conquer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	});

	if (DEBUG) std::cout << "[Main] Successfully setup window" << std::endl;
	return window;
}

int main(int argc, char* argv[]) {

	std::vector<std::tuple<std::string, int, int>> tests;
	tests.push_back(std::make_tuple("1 Ant", 10, 1));
	tests.push_back(std::make_tuple("10 Ants", 10, 10));
	tests.push_back(std::make_tuple("100 Ants", 10, 100));
	tests.push_back(std::make_tuple("1000 Ants", 10, 1000));
	GLFWwindow* window;
	GameWindow* gameWindow;

	for (auto const& test : tests) {
		if (DEBUG) std::cout << "[Main] Starting application " << get<0>(test) << std::endl;
		window = setup_glfw_window();
		gameWindow = new GameWindow(window, 10, get<2>(test));

		if (DEBUG) std::cout << "[Main] Terminating program " << get<0>(test) << std::endl << std::endl;
		delete gameWindow;
		glfwTerminate();
	}

	return 0;
}


