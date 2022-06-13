#include "GameWindow.h"

#include <iostream>
#include <string>

#include "globals.h"
#include "TextureManager.h"
#include "Shader.h"
#include "StaticImage.h"
#include "SpriteSheet.h"

#include "Player.h"
#include "Ant.h" //<- temporary testing of ant movement, likely goes in Game.cpp

GameWindow::GameWindow(GLFWwindow* w) :
	window(w),
	server(nullptr)
{
	gameLoop();
}

void GameWindow::gameLoop(void) {
	StaticImage background("cac_screenshot.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));

	SpriteSheet antSprite("ant.png", 0.1, 0.1, 8);

	Player* player = new Player();
	Ant antTest(*player, glm::vec2(0.1f, 0.1f));
	antTest.updateAcc(glm::vec2(0.0001f, -0.0001f));

	glfwSetTime(0);
	float currTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		background.draw();

		antTest.update((currTime = glfwGetTime() - currTime));
		antSprite.drawSprite(antTest.drawSettings());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void GameWindow::processKeyboardInput(void) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

