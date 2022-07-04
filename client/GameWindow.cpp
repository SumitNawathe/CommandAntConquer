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

	SpriteSheet antSprite("ant.png", 0.075, 0.075, 8);

	Player player(glm::vec2(0.39f, 0.45f));
	constexpr int NUM_ANTS = 4;
	for (int i = 0; i < NUM_ANTS; i++) {
		Ant a(player, glm::vec2(((double)rand() / (double)RAND_MAX) * 1.8 - 0.9, ((double)rand() / (double)RAND_MAX) * 1.8 - 0.9));
		player.ants.push_back(a);
		player.sentryPosts.add(a.getID());
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
		setPlayerInputs(player);

		currTime = glfwGetTime();
		deltaTime = currTime - lastTime;

		player.update(deltaTime);
		//antTest.update(deltaTime);
		for (int i = 0; i < player.ants.size(); i++) {
			//for (int j = i+1; j < player.ants.size(); j++) {
				//Ant& aAnt = player.ants.at(i);
				//Ant& bAnt = player.ants.at(j);
				//if (glm::distance(aAnt.getPos(), bAnt.getPos()) < 0.08f) {
					//aAnt.addVel((aAnt.getPos() - bAnt.getPos()) / 100.0f);
					//bAnt.addVel((bAnt.getPos() - aAnt.getPos()) / 100.0f);
				//}
			//}
			player.ants.at(i).update(deltaTime);
		}

		if (currTime - frameTime >= FPS_LIMIT) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			background.draw();
			//antSprite.drawSprite(antTest.drawSettings());
			for (auto& ant : player.ants) {
				antSprite.drawSprite(ant.drawSettings());
			}

			antSprite.drawSprite(player.drawSettings());

			glfwSwapBuffers(window);
			glfwPollEvents();

			frameTime = currTime;
		}
		lastTime = currTime;
	}

}

void GameWindow::setPlayerInputs(Player& player) {
	bool up = false, down = false, left = false, right = false;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) up = true;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) down = true;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) left = true;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) right = true;
	
	if (up && !down) player.inputDirection.setUp();
	else if (down && !up) player.inputDirection.setDown();
	else player.inputDirection.setNeutVert();

	if (left && !right) player.inputDirection.setLeft();
	else if (right && !left) player.inputDirection.setRight();
	else player.inputDirection.setNeutHoriz();

	if constexpr (DEBUG) {
		static bool prevUp, prevDown, prevLeft, prevRight;
		if (up != prevUp) std::cout << "[GameWindow::setPlayerInputs] UP "
			<< ( (prevUp = up) ? "pressed" : "released" ) << '\n';
		if (down != prevDown) std::cout << "[GameWindow::setPlayerInputs] DOWN "
			<< ( (prevDown = down) ? "pressed" : "released" ) << '\n';
		if (left != prevLeft) std::cout << "[GameWindow::setPlayerInputs] LEFT "
			<< ( (prevLeft = left) ? "pressed" : "released" ) << '\n';
		if (right != prevRight) std::cout << "[GameWindow::setPlayerInputs] RIGHT "
			<< ( (prevRight = right) ? "pressed" : "released" ) << '\n';
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
