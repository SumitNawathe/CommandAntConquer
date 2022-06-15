#include "Map.h"

#include <iostream>
#include <fstream>
#include <regex>

Map::Map(const char* directory) {
	if (!directory) {
		std::cout << "[Map] constructor argument is nullptr" << std::endl;
		exit(-1);
	}

	std::ifstream infile(directory);
	// do regex matching based on file structure (discord)
}


