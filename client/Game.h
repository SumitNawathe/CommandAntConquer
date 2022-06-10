#pragma once

#include <vector>

#include "forward_declarations.h"
#include "Player.h"
#include "Map.h"

class Game {
public:
	void drawSprites(void);
	// lots of timers and socket stuff

private:
	std::vector<Player> players;
	Map map;
};

