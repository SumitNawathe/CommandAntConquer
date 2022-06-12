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

	/*
    Shader shader(
        "C:/Users/Sumit Nawathe/source/repos/CommandAntConquer/CommandAntConquer/CommandAntConquer/client/shaders/static_image_shader.vert",
        "C:/Users/Sumit Nawathe/source/repos/CommandAntConquer/CommandAntConquer/CommandAntConquer/client/shaders/static_image_shader.frag"
    );
	TextureManager::getInstance().registerTexture("cac_screenshot.png");
	unsigned int id = TextureManager::getInstance().getTextureID("cac_screenshot.png");
	std::cout << "[GameWindow::gameLoop] id: " << id << std::endl;

	shader.use();
	//shader.setInteger("texture1", id);
	glUniform1i(glGetUniformLocation(shader.id, "texture1"), 0);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/

	StaticImage background("cac_screenshot.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));

	SpriteSheet antTest("ant.png", 16, 8, 8, 8);

	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		glBindTexture(GL_TEXTURE_2D, id);
		glBindVertexArray(VAO);
		shader.use();
		glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
		*/
		background.draw();
		antTest.drawSprite(0.5, 0.5, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void GameWindow::processKeyboardInput(void) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

