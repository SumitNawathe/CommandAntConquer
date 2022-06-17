#include <string>

class GameMap
{
public:
	
	// initialize internal information of map from file
	// specified by the input string
	void SerializeFromString(const char const* path); 
	
	// returns whether the point at (x,y) is within a 
	// restricted region
	bool Restricted(double x, double y);

	// returns the point that is nearest to the inputted point 
	// (will likely be on an edge)
	// if x,y are non-restricted, then they are returned
	// if there are multiple nearest non-restricted points, 
	// then any arbitrary one is chosen
	int* NearestNonrestricted(double x, double y);

	// name of the map
	char* mapName;

	// number of players
	int numPLayers;

	// pointer to a pointer to an int array of size 2 with first element
	// being x and second element being y
	int** depots;

	// pointer to a pointer to an int array of size 2 with first element
	// being x and second element being y
	int** nests;

private:
	enum TILE_TYPE {fullyRestricted, partiallyRestricted, notRestricted, notWithinMap};
	
	int dimWidth; // width of the tileArray
	int dimHeight; // height of the tileArray

	int* tiles; // double array of tiles, but encoded as a single array

	TILE_TYPE getTileType(double x, double y); // returns what type of tile is the input coordinate
											   // within


	// number of tiles from one end of the board to the other
	const int /* keep this number EVEN */ numTiles = 128;
};

