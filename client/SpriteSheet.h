#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

class SpriteSheet {
public:
	SpriteSheet(const char* imageName, float tW, float tH, float sW);
	void drawSprite(float posX, float posY, int frameNum);

private:
	const char* imageName;
	int spriteWidth, spriteHeight;
	int texWidth, texHeight;
	unsigned int VAO, VBO;
	Shader shader;
	unsigned int textureID;
	int fileWidth;
};

