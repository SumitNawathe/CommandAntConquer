#include "TextureManager.h"

#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"

#include "globals.h"

void TextureManager::registerTexture(const char* textureName) {
	int width, height, numChannels;
	std::string loc = std::string(IMAGES_DIR) + textureName;
	unsigned char* data = stbi_load(loc.c_str(), &width, &height, &numChannels, 0);
	if (!data) {
		std::cout << "Failed to load texture at " << loc << std::endl;
		exit(-1);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(data);

	if (DEBUG) std::cout << "[TextureManager] Successfully loaded image at "
		<< loc << "; width = " << width
		<< ", height = " << height
		<< ", numChannels = " << numChannels
		<< ", textureID = " << textureID << std::endl;
	textures[textureName] = textureID;
}

