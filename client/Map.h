#pragma once

#include <vector>
#include <string>

#include "forward_declarations.h"
#include "Depot.h"
#include "Nest.h"
#include "StaticImage.h"

class Map {
public:
	typedef typename std::vector<glm::vec2> Boundary;

	Map(const char* directory);

private:
	std::string name;
	int numPlayers;
	StaticImage* foreground;
	StaticImage* background;
	std::vector<Depot> depots;
	std::vector<Nest> nests;
	Boundary mapEdge;
	std::vector<Boundary> rocks;
	int boundaryApproxGridWidth, boundaryApproxGridHeight;
	int** boundaryApproxGrid; // boundaryApproxGrid[width][height], heap-allocated
};

