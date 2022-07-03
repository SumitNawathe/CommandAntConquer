#include "Ant.h"

#include <glad/glad.h>
#include "TextureManager.h"
#include <iostream>
#include <glm/gtx/projection.hpp>
#include <chrono>

#include "utils.h"
#include "Player.h"

Ant::Ant(Player& player, glm::vec2 pos) :
	alive(true),
	state(AntState::Standing),
	carrying(AntCarrying::Empty),
	player(player),
	pos(pos),
	vel(0),
	acc(0),
	speed(0),
	walk(0),
	step(0),
	id(genID())
{
	
	depot = new Depot(glm::vec2(0.745f, -0.1f));
	std::cout << player.getNest()->getPos().x << " " << player.getNest()->getPos().y << std::endl;

	// for testing only
	//state = AntState::GettingFood;
	state = AntState::Sentry;
}

void Ant::updateAccTowardsTarget(glm::vec2 target, bool antiOrbit) {
	glm::vec2 acc = target - pos;

	if (antiOrbit) {
		glm::vec3 normal = glm::cross(vec2to3(acc), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 proj = glm::proj(vec2to3(vel), normal);
		
		if (glm::length(proj) > 10.0f * ANT_MIN_SPEED_THRESHOLD)
			acc -= vec3to2(proj);
	}
	setAcc(acc);
}

void Ant::update(float dt) {
	switch (state) {
		case AntState::GettingFood:
			if (glm::distance(pos, depot->getPos()) < 0.08f) {
				carrying = AntCarrying::Food;
				state = AntState::DeliveringFood;
				setAcc(player.getNest()->getPos() - pos);
			}
			else {
				updateAccTowardsTarget(depot->getPos());
			}
			break;
		case AntState::DeliveringFood:
			if (glm::distance(pos, player.getNest()->getPos()) < 0.08f) {
				carrying = AntCarrying::Empty;
				state = AntState::GettingFood;
				setAcc(depot->getPos() - pos);
			}
			else {
				updateAccTowardsTarget(player.getNest()->getPos());
			}
			break;
		case AntState::Sentry:
			glm::vec2 target = player.sentryPosts.getRelPos(id) + player.getPos();
			updateAccTowardsTarget(target);
			if (glm::distance(target, pos) < 0.001f) {
				pos = target;
				vel = glm::vec2(0.0f, 0.0f);
				acc = glm::vec2(0.0f, 0.0f);
			}
			break;
		default:
			break;
	}
	runPhysics(dt);
}

void Ant::runPhysics(float dt) {
	vel += dt * acc;
	updateSpeed();
	updateWalk(dt);
	pos += dt * vel;
}

void Ant::updateSpeed() {
	speed = glm::length(vel);
	if (speed > ANT_MAX_SPEED) {
		vel = glm::normalize(vel) * ANT_MAX_SPEED;
		speed = ANT_MAX_SPEED;
	}
}

void Ant::updateWalk(double dt) {
	walk += dt;
	float threshold = 1.0f / (50.0f * speed);
	//std::cout << "walk: " << walk << " inverse speed: " << threshold << std::endl;
	if (walk > threshold) {
		walk = 0;
		step = !step;
	}
}

std::tuple<glm::vec2, int, int> Ant::drawSettings() const {
	int direction = acc.x < 0;
	switch (carrying) {
		case AntCarrying::Empty:
			return std::make_tuple(pos, step, direction);
		case AntCarrying::Food:
		case AntCarrying::Egg:
			return std::make_tuple(pos, step + 2, direction);
	}
}

const Ant::ID_T Ant::genID(void) const {
	return genRandLL();
}
