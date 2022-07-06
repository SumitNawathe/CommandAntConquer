#include "Ant.h"
#include <glad/glad.h>
#include "TextureManager.h"
#include <iostream>
#include <glm/gtx/projection.hpp>
#include "utils.h"

Ant::Ant(Player& player, glm::vec2 pos) :
	MAX_SPEED(0.18),
	MIN_SPEED_THRESHOLD(0.001),
	alive(1),
	state(AntState::Standing),
	carrying(AntCarrying::Empty),
	player(player),
	pos(pos),
	vel(0),
	acc(0),
	speed(0),
	walk(0),
	step(0)
{
	
	depot = new Depot(glm::vec2(0.745f, -0.1f));
	state = AntState::GettingFood; //<- for testing only
	//std::cout << player.getNest()->getPos().x << " " << player.getNest()->getPos().y << std::endl;
}

glm::vec2 Ant::getPos() {
	return pos;
}

glm::vec2 Ant::getVel() {
	return vel;
}

void Ant::updateAccTowardsTarget(glm::vec2 target, bool antiOrbit) {
	glm::vec2 acc = target - pos;

	if (antiOrbit) {
		glm::vec3 normal = glm::cross(vec2to3(acc), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 proj = glm::proj(vec2to3(vel), normal);
		
		if (glm::length(proj) > 10.0f * MIN_SPEED_THRESHOLD)
			acc -= vec3to2(proj);
	}
	setAcc(acc);
}

void Ant::update(float dt) {
	if (state == AntState::GettingFood) {
		if (glm::distance(pos, depot->getPos()) < 0.08f) {
			carrying = AntCarrying::Food;
			state = AntState::DeliveringFood;
			setAcc(player.getNest()->getPos() - pos);
		}
		else {
			updateAccTowardsTarget(depot->getPos());
		}
	}
	else if (state == AntState::DeliveringFood) {
		if (glm::distance(pos, player.getNest()->getPos()) < 0.08f) {
			carrying = AntCarrying::Empty;
			state = AntState::GettingFood;
			setAcc(depot->getPos() - pos);
		}
		else {
			updateAccTowardsTarget(player.getNest()->getPos());
		}
	}
	runPhysics(dt);
}

void Ant::runPhysics(float dt) {
	vel += dt * acc;
	updateSpeed();
	updateWalk(dt);
	pos += dt * vel;
}

void Ant::setAcc(glm::vec2 acc) {
	this->acc = acc;
}

void Ant::updateSpeed() {
	speed = glm::length(vel);
	if (speed > MAX_SPEED) {
		vel = glm::normalize(vel) * MAX_SPEED;
		speed = MAX_SPEED;
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

void Ant::addVel(glm::vec2 vel) {
	this->vel += vel;
}

std::tuple<glm::vec2, int, int> Ant::drawSettings() {
	int direction = acc.x < 0;
	if (carrying == AntCarrying::Empty) {
		//if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, step, direction);
	}
	else if (carrying == AntCarrying::Food || carrying == AntCarrying::Egg) {
		//if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, step + 2, direction);
	}
}