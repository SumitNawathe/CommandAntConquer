#include "Ant.h"
#include <glad/glad.h>
#include "TextureManager.h"
#include <iostream>

Ant::Ant(Player& player, glm::vec2 pos) :
	MAX_SPEED(0.001),
	MIN_SPEED_THRESHOLD(0.001),
	MAX_ACCELERATION(0.0001),
	alive(1),
	state(AntState::Standing),
	carrying(AntCarrying::Empty),
	player(player),
	pos(pos),
	vel(0),
	acc(0),
	speed(0),
	step(0)
{
	depot = new Depot(glm::vec2(0.745f, -0.1f));

	state = AntState::GettingFood; //<- for testing only
}

glm::vec2 Ant::getVel() {
	return vel;
}

void Ant::update(float dt) {
	if (state == AntState::GettingFood) {
		if (glm::distance(pos, depot->getPos()) < 0.01f) {
			carrying = AntCarrying::Food;
			state = AntState::DeliveringFood;
			updateAcc(glm::normalize(player.getNest()->getPos() - pos) / 10.0f);
		}
		else {
			updateAcc(glm::normalize(depot->getPos() - pos) / 10.0f);
		}
	}
	else if (state == AntState::DeliveringFood) {
		if (glm::distance(pos, player.getNest()->getPos()) < 0.01f) {
			carrying = AntCarrying::Empty;
			state = AntState::GettingFood;
			updateAcc(glm::normalize(depot->getPos() - pos) / 10.0f);
		}
		else {
			updateAcc(glm::normalize(player.getNest()->getPos() - pos) / 10.0f);

		}
	}
	vel = vel + dt * acc;
	updateSpeed();
	std::cout << "speed: " << speed << " vel: " << vel.x << " " << vel.y << std::endl;
	pos = pos + dt * vel;
}

void Ant::updateAcc(glm::vec2 acc) {
	if (glm::length(acc) > MAX_ACCELERATION) {
		this->acc = glm::normalize(acc) * MAX_ACCELERATION;
		return;
	}
	this->acc = acc;
}

void Ant::updateSpeed() {
	speed = glm::length(vel);
	if (speed > MAX_SPEED) {
		vel = glm::normalize(vel) * MAX_SPEED;
		speed = MAX_SPEED;
	}
}

std::tuple<glm::vec2, int> Ant::drawSettings() {
	if (carrying == AntCarrying::Empty) {
		if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, (step = !step));
	}
	else if (carrying == AntCarrying::Food || carrying == AntCarrying::Egg) {
		if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, (step = !step) + 2);
	}
}