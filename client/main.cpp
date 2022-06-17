#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "forward_declarations.h"
#include "globals.h"
#include "GameWindow.h"
#include "Map.h"

int main(int argc, char* argv[]) {
	GameMap f;
	f.SerializeFromString("C:/Users/ezhu2/Desktop/Trash.txt");


	return 0;
}
