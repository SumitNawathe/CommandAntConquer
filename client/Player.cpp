#include "Player.h"

Player::Player(glm::vec2 pos)
{
	nest = new Nest(pos, *this);
}

Nest* Player::getNest() {
	return nest;
}