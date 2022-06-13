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
	Ant antTest(*player, glm::vec2(0.39f, 0.45f));


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
