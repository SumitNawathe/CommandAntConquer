#include "StaticImage.h"

#include <glad/glad.h>

#include "TextureManager.h"

StaticImage::StaticImage(const char* imageName, const glm::vec2 bottomLeft, const glm::vec2 topRight) :
	imageName(imageName),
	bottomLeft(bottomLeft),
	topRight(topRight),
	shader(
		"CommandAntConquer/client/shaders/static_image_shader.vert",
		"CommandAntConquer/client/shaders/static_image_shader.frag"
	),
	VAO(0),
	VBO(0),
	textureID(0)
{
	// set up texture
	TextureManager::getInstance().registerTexture(imageName);
	textureID = TextureManager::getInstance().getTextureID(imageName);
	shader.setInteger("texture1", 0, true);

	// set up VAO/VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	const float vertices[] = {
		bottomLeft.x,	bottomLeft.y,	0.0f, 0.0f, // bottom left
		topRight.x,		bottomLeft.y,	1.0f, 0.0f, // bottom right
		topRight.x,		topRight.y,		1.0f, 1.0f, // top right

		bottomLeft.x,	bottomLeft.y,	0.0f, 0.0f, // bottom left
		topRight.x,		topRight.y,		1.0f, 1.0f, // top right
		bottomLeft.x,	topRight.y,		0.0f, 1.0f	// top left
	};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void StaticImage::draw() {
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader.use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

