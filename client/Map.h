#pragma once

#include <vector>

#include "forward_declarations.h"
#include "Depot.h"
#include "Nest.h"

class Map {
public:
	void drawBackground(void);
	void drawForeground(void);

private:
	std::vector<Depot> depots;
	std::vector<Nest> nests;

	void loadMap(const char* directory);
};

