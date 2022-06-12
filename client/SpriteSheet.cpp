#include "SpriteSheet.h"
#include <glad/glad.h>

SpriteSheet::SpriteSheet(const char* imageName, int tW, int tH, int sW, int sH) :
	imageName(imageName), texWidth(tW), texHeight(tH), spriteWidth(sW), spriteHeight(sH)
{

}

void SpriteSheet::drawSprite(float posX, float posY, int frameIndex) {
	const float verts[] = {
		posX, posY,
		posX + spriteWidth, posY,
		posX + spriteWidth, posY + spriteHeight,
		posX, posY + spriteHeight
	};
    const float tw = float(spriteWidth) / texWidth;
    const float th = float(spriteHeight) / texHeight;
    const int numPerRow = texWidth / spriteWidth;
    const float tx = (frameIndex % numPerRow) * tw;
    const float ty = (frameIndex / numPerRow + 1) * th;
    const float texVerts[] = {
        tx, ty,
        tx + tw, ty,
        tx + tw, ty + th,
        tx, ty + th
    };

    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}