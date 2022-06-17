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

//debug
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GameWindow::GameWindow(GLFWwindow* w) :
	FPS_LIMIT(1.0 / 60.0),
	window(w),
	server(nullptr)
{
	gameLoop();
}

void GameWindow::gameLoop(void) {

	if (DEBUG) glfwSetMouseButtonCallback(window, mouse_button_callback);

	StaticImage background("cac_screenshot.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));

	SpriteSheet antSprite("ant.png", 0.1, 0.1, 8);

	Player* player = new Player(glm::vec2(0.39f, 0.45f));
	std::vector<Ant> ants;
	//Ant antTest(*player, glm::vec2(0.39f, 0.45f));
	for (int i = 0; i < 10000; i++) {
		ants.push_back(Ant(*(new Player(glm::vec2(((double)rand() / (double)RAND_MAX) * 1.8 - 0.9, ((double)rand() / (double)RAND_MAX) * 1.8 - 0.9))),
			glm::vec2(((double)rand() / (double)RAND_MAX) * 1.8 - 0.9, ((double)rand() / (double)RAND_MAX) * 1.8 - 0.9)));
	}


	glfwSetTime(0);
	double lastTime = glfwGetTime();
	double deltaTime = 0;
	double currTime = 0;
	double frameTime = 0;
	double renderTime = 0;

	glm::vec2 pos(0, 0);

	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();

		currTime = glfwGetTime();
		deltaTime = currTime - lastTime;

		//antTest.update(deltaTime);

		for (auto& ant : ants) {
			ant.update(deltaTime);
		}

		if (currTime - frameTime >= FPS_LIMIT) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			background.draw();
			for (auto& ant : ants) {
				antSprite.drawSprite(ant.drawSettings());
			}

			glfwSwapBuffers(window);
			glfwPollEvents();

			frameTime = currTime;
		}
		lastTime = currTime;
	}

}

void GameWindow::processKeyboardInput(void) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//debug

void mouse_button_callback(GLFWwindow* _window, int button, int action, int mods)
 {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		double xpos, ypos;
		glfwGetCursorPos(_window, &xpos, &ypos);
		std::cout << "Cursor Position at (" << 2.0f * ((float)(xpos/width)) - 1.0f
			<< " : " << 1.0f - 2.0f * ((float)(ypos/height)) << ")" << std::endl;
	}
 }
