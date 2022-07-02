#pragma once

#include <glm/glm.hpp>

#include "forward_declarations.h"
#include "Depot.h"

/* possible states representing actions an Ant could be performing */
enum class AntState {
	Standing,
	Sentry,
	Attacking,
	GettingFood,
	DeliveringFood
};

/* possible state of what the ant could be holding */
enum class AntCarrying {
	Empty,
	Food,
	Egg
};

/* constants/definitions used in main class */

constexpr float ANT_MAX_SPEED = 0.25f;
constexpr float ANT_MIN_SPEED_THRESHOLD = 0.001f;

class Ant {
public:
	Ant(Player& player, glm::vec2 pos);

	glm::vec2 getPos() const { return pos; }
	glm::vec2 getVel() const { return vel; }

	typedef long long int ID_T;
	const ID_T getID() { return id; }

	void update(float dt);
	void setAcc(glm::vec2 acc) { this->acc = acc; }
	void updateSpeed();
	void updateWalk(double dt);
	void addVel(glm::vec2 v) { vel += v; }

	std::tuple<glm::vec2, int, int> drawSettings() const;

private:
	/* Ant's ID, unique among ants belonging to the same player during a game */
	const ID_T id;

	bool alive;
	Player& player;

	AntState state;
	AntCarrying carrying;
	union {
		Depot* depot;
		int sentryIndex;
	};

	/* properties for movement */

	glm::vec2 pos;
	glm::vec2 vel;
	glm::vec2 acc;
	float speed;

	/* properties for animation */

	double walk;
	int step;

	void updateAccTowardsTarget(glm::vec2 target, bool antiOrbit = true);
	void runPhysics(float dt);
	const ID_T genID(void) const;
};


