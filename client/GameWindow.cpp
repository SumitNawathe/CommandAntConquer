#include "GameWindow.h"

#include <iostream>
#include <string>

#include "globals.h"
#include "TextureManager.h"
#include "Shader.h"
#include "StaticImage.h"
#include "SpriteSheet.h"

GameWindow::GameWindow(GLFWwindow* w) :
	window(w),
	server(nullptr)
{
	gameLoop();
}

void GameWindow::gameLoop(void) {
	StaticImage background("cac_screenshot.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));

	SpriteSheet antTest("ant.png", 0.1, 0.1, 8);

	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		background.draw();
		antTest.drawSprite(0.5, 0.5, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void GameWindow::processKeyboardInput(void) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

