#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "forward_declarations.h"
#include "Ant.h"
#include "Nest.h"

class Player {
public:
	Player(glm::vec2 pos);
	void update(float dt);
	Nest* getNest();

private:
	glm::vec2 queenPos;
	std::vector<Ant> ants;
	Nest* nest;
	glm::vec2 pos;
	glm::vec2 vel;
	float speed;
};

