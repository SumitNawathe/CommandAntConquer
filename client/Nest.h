#pragma once

#include "forward_declarations.h"
#include "Player.h"

class Nest {
public:
	Nest(glm::vec2 pos, Player& player);
	glm::vec2 getPos();
private:
	glm::vec2 pos;
	Player& player;
	int score;
};
