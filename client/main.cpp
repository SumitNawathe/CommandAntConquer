#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "forward_declarations.h"
#include "globals.h"
#include "GameWindow.h"

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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	});

	if (DEBUG) std::cout << "[Main] Successfully setup window" << std::endl;
	return window;
}

int main(int argc, char* argv[]) {
	if (DEBUG) std::cout << "[Main] Starting application" << std::endl;
	GLFWwindow* window = setup_glfw_window();
	GameWindow gameWindow(window);

	if (DEBUG) std::cout << "[Main] Terminating program" << std::endl;
	glfwTerminate();
	return 0;
}

