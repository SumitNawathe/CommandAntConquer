#pragma once

#include <glm/glm.hpp>

#include "forward_declarations.h"

class Depot {
public:
	Depot(glm::vec2 pos);
	glm::vec2 getPos();
private:
	glm::vec2 pos;
	int supply;
};
