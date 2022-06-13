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
	void updateAcc(glm::vec2 acc);
	void updateSpeed();
	std::tuple<glm::vec2, int> drawSettings();

private:
	const float MAX_SPEED;
	const float MIN_SPEED_THRESHOLD;

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
	glm::vec2 acc;
	float speed;

	int step;
};


