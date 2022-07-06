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
bool checkAntCollision(Ant& a, Ant& b);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GameWindow::GameWindow(GLFWwindow* w) :
	FPS_LIMIT(1.0 / 60.0),
	window(w),
	server(nullptr)
{
	gameLoop();
}

GameWindow::GameWindow(GLFWwindow* w, int timeSeconds, int numAnts) :
	FPS_LIMIT(1.0 / 60.0),
	window(w),
	server(nullptr),
	timeSeconds(timeSeconds),
	numAnts(numAnts)
{
	gameLoop();
}

void GameWindow::gameLoop(void) {

	if (DEBUG) glfwSetMouseButtonCallback(window, mouse_button_callback);

	StaticImage background("cac_screenshot.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));

	SpriteSheet antSprite("ant.png", 0.05, 0.05, 8);

	Player* player = new Player(glm::vec2(0.39f, 0.45f));
	std::vector<Ant> ants;
	//Ant antTest(*player, glm::vec2(0.39f, 0.45f));
	const int NUM_ANTS = numAnts;
	for (int i = 0; i < NUM_ANTS; i++) {
		//Player* tempPlayer = new Player(glm::vec2(((double)rand() / (double)RAND_MAX) * 1.8 - 0.9, ((double)rand() / (double)RAND_MAX) * 1.8 - 0.9));
		//ants.push_back(Ant(*tempPlayer, tempPlayer->getNest()->getPos()));
		ants.push_back(Ant(*player, glm::vec2(((double)rand() / (double)RAND_MAX) * 1.8 - 0.9, ((double)rand() / (double)RAND_MAX) * 1.8 - 0.9)));
	}


	glfwSetTime(0);
	double lastTime = glfwGetTime();
	double deltaTime = 0;
	double currTime = 0;
	double frameTime = 0;
	double renderTime = 0;
	
	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();

		currTime = glfwGetTime();
		deltaTime = currTime - lastTime;
		approxdT = (approxdT + deltaTime) / 2.0;

		//antTest.update(deltaTime);
		for (int i = 0; i < ants.size(); i++) {
			for (int j = i+1; j < ants.size(); j++) {
				Ant& aAnt = ants.at(i);
				Ant& bAnt = ants.at(j);
				if (checkAntCollision(aAnt, bAnt)) {
					aAnt.addVel((.05f * glm::normalize(aAnt.getPos() - bAnt.getPos()) - (aAnt.getPos() - bAnt.getPos())) * 20.0f * (float)deltaTime);
					bAnt.addVel((.05f * glm::normalize(bAnt.getPos() - aAnt.getPos()) - (bAnt.getPos() - aAnt.getPos())) * 20.0f * (float)deltaTime);
				}
			}
			ants.at(i).update(deltaTime);
		}

		if (currTime - frameTime >= FPS_LIMIT) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			background.draw();
			//antSprite.drawSprite(antTest.drawSettings());
			for (auto& ant : ants) {
				antSprite.drawSprite(ant.drawSettings());
			}

			glfwSwapBuffers(window);
			glfwPollEvents();

			frameTime = currTime;
		}
		lastTime = currTime;
		if (currTime > timeSeconds) {
			glfwSetWindowShouldClose(window, true);
			std::cout << "Approximate deltaTime: " << approxdT << std::endl;
		}
	}

}

void GameWindow::processKeyboardInput(void) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		std::cout << "Approximate deltaTime: " << approxdT << std::endl;
	}
}

//debug
bool checkAntCollision(Ant& a, Ant& b) {
	return a.getPos().x + 0.05 >= b.getPos().x && b.getPos().x + 0.05 >= a.getPos().x &&
		a.getPos().y + 0.05 >= b.getPos().y && b.getPos().y + 0.05 >= a.getPos().y;
	//return glm::distance(a.getPos(), b.getPos()) < 0.05f;
}

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
