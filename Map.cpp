#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void GameMap::SerializeFromString(const char const* path) {
    // reading a text file

    string line;
    ifstream myfile(path);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

bool GameMap::Restricted(double x, double y) {
    return false;
}

int* GameMap::NearestNonrestricted(double x, double y) {
    return nullptr;
}

GameMap::TILE_TYPE GameMap::getTileType(double x, double y) {
    return Map::fullyRestricted;
}