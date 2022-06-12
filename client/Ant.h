#pragma once

#include <glm/glm.hpp>

#include "forward_declarations.h"
#include "Depot.h"
#include "Player.h"

enum class AntState {
	Standing,
	Sentry,
	Attacking,
	GettingFood,
	DeliveringFood
};

enum class AntCarrying {
	Empty,
	Food,
	Egg
};

class Ant {
public:
	Ant(Player& player, glm::vec2 pos);
	void update(float dt);

private:
	bool alive;
	AntState state;
	AntCarrying carrying;
	union {
		Depot* depot;
		int sentryIndex;
	};
	Player& player;
	glm::vec2 pos;
	glm::vec2 vel;
	float speed;
};


