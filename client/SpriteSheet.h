#pragma once

class SpriteSheet {
	const char* imageName;
	int spriteWidth, spriteHeight;
	int texWidth, texHeight;


public:
	SpriteSheet(const char* imageName, int tW, int tH, int sW, int sH);
	void drawSprite(float posX, float posY, int frameIndex);
};
