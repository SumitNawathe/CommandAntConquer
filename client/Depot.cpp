#include "Depot.h"

Depot::Depot(glm::vec2 pos) :
	pos(pos),
	supply(0)
{

}

glm::vec2 Depot::getPos() {
	return pos;
}