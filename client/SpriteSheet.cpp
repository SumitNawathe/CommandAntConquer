#include "SpriteSheet.h"
#include <glad/glad.h>
#include <iostream>
#include "TextureManager.h"

// t*: texture, on screen
// s*: spritesheet, OpenGL texture coordinates

/*
* SpriteSheet constructor, only one should be instantiated for each type of sprite
* @param imageName: relative path to image should be IMAGES_DIR + imageName
* @param tW/tH: dimensions of the sprite as they will be drawn on screen (in screen-space coords)
* @param sW: the width of the sprite texture in the texture file (in texture-space coords). Should be 1.0f / (num animation frames).
* Note that sH = 1, since frames are stored horizontally, each frame takes full vertical space of texture file
*/
SpriteSheet::SpriteSheet(const char* imageName, float tW, float tH, float sW) :
    imageName(imageName),
    texWidth(tW),
    texHeight(tH),
    spriteWidth(sW),
    shader(
        "client/shaders/sprite_shader.vert",
        "client/shaders/sprite_shader.frag"
    ),
    VAO(0),
    VBO(0),
    textureID(0)
{
    // setup texture/shader
    auto [fw, _] = TextureManager::getInstance().registerTexture(imageName);
    fileWidth = fw;
    textureID = TextureManager::getInstance().getTextureID(imageName);
    shader.setInteger("texture1", 0, true);
    if (DEBUG) std::cout << "[SpriteSheet] fileWidth = " << fileWidth << std::endl;

    // set up VAO/VBO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	const float vertices[] = {
        -tW/2.0f, -tH/2.0f, 0.0f,                   0.0f,    // bottom left
         tW/2.0f, -tH/2.0f, sW / (float)fileWidth,  0.0f,    // bottom right
         tW/2.0f,  tH/2.0f, sW / (float)fileWidth,  1.0f,    // top right

        -tW/2.0f, -tH/2.0f, 0.0f,                   0.0f,    // bottom left
         tW/2.0f,  tH/2.0f, sW / (float)fileWidth,  1.0f,    // top right
        -tW/2.0f,  tH/2.0f, 0.0f,                   1.0f     // top left
	};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void SpriteSheet::drawSprite(float posX, float posY, int frameNumber) {
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.use();
    shader.setVector2f("actualPosition", posX, posY);
    shader.setInteger("frameNum", frameNumber);
    shader.setFloat("frameHorizSize", (float)spriteWidth / (float)fileWidth);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteSheet::drawSprite(std::tuple<glm::vec2, int> settings) {
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.use();
    shader.setVector2f("actualPosition", (get<0>(settings)).x, (get<0>(settings)).y);
    shader.setInteger("frameNum", get<1>(settings));
    shader.setFloat("frameHorizSize", (float)spriteWidth / (float)fileWidth);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}

void SpriteSheet::drawSprite(std::tuple<glm::vec2, int, int> settings) {
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.use();
    shader.setVector2f("actualPosition", (get<0>(settings)).x, (get<0>(settings)).y);
    shader.setInteger("frameNum", get<1>(settings));
    shader.setFloat("frameHorizSize", (float)spriteWidth / (float)fileWidth);
    shader.setInteger("direction", get<2>(settings));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}
