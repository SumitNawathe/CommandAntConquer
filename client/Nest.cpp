#include "Nest.h"

Nest::Nest(glm::vec2 pos, Player& player) :
	pos(pos),
	player(player)
{

}

glm::vec2 Nest::getPos() {
	return pos;
}