#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

class SpriteSheet {
public:
	SpriteSheet(const char* imageName, float tW, float tH, float sW);
	void drawSprite(float posX, float posY, int frameNum);
	void drawSprite(std::tuple<glm::vec2, int>);
	void drawSprite(std::tuple<glm::vec2, int, int>);

private:
	const char* imageName;
	int spriteWidth;
	int texWidth, texHeight;
	unsigned int VAO, VBO;
	Shader shader;
	unsigned int textureID;
	int fileWidth;
};

