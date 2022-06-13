#include "Ant.h"
#include <glad/glad.h>
#include "TextureManager.h"

Ant::Ant(Player& player, glm::vec2 pos) :
	MAX_SPEED(0.001),
	MIN_SPEED_THRESHOLD(0.000001),
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
	
}

void Ant::update(float dt) {
	vel = vel + dt * acc;
	updateSpeed();
	if (speed > MAX_SPEED) vel = glm::normalize(vel) * MAX_SPEED;
	pos = pos + dt * vel;
}

void Ant::updateAcc(glm::vec2 acc) {
	this->acc = acc;
}

void Ant::updateSpeed() {
	speed = glm::length(vel);
}

std::tuple<glm::vec2, int> Ant::drawSettings() {
	if (carrying == AntCarrying::Empty) {
		if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, (step = !step));
	}
	else if (carrying == AntCarrying::Food || carrying == AntCarrying::Egg) {
		if (speed < MIN_SPEED_THRESHOLD) return std::make_tuple(pos, 0);
		return std::make_tuple(pos, (step = !step));
	}
}