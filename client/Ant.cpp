#include "Ant.h"
#include <glad/glad.h>
#include "TextureManager.h"

Ant::Ant(Player& player, glm::vec2 pos) :
	alive(1),
	state(AntState::Standing),
	carrying(AntCarrying::Empty),
	player(player),
	pos(pos),
	vel(0),
	speed(0)
{
	
}