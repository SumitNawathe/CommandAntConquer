#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

class SpriteSheet {
public:
	SpriteSheet(const char* imageName, int tW, int tH, int sW, int sH);
	void drawSprite(float posX, float posY);

private:
	const char* imageName;
	int spriteWidth, spriteHeight;
	int texWidth, texHeight;
	unsigned int VAO, VBO;
	Shader shader;
	unsigned int textureID;
};
