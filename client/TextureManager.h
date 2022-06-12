#pragma once

#include <map>
#include <string>
#include "stb_image.h"

class TextureManager {
public:
	static TextureManager& getInstance() {
		static TextureManager instance;
		return instance;
	}
	void registerTexture(const char* textureName);
	unsigned int getTextureID(const char* tex) { return textures[tex]; }

private:
	std::map<const char*, unsigned int> textures;
	TextureManager() { stbi_set_flip_vertically_on_load(true); }
};

