#pragma once

/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 4 - Inclusion of lighting effects to the game
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include "constants.h"
#include "next_direction.h"
#include "ghost.h"

class Map {

public:
	int COLUMNS, ROWS, COLUMNS2;
	char** mapSurface;
	char** mapSurface2;
	int rowHalf;
	int columnHalf;
	int  startingPoint[2];

public:
	void set_values();
	void initiateMap();
	void drawBorders();
	void drawCenter();
	void mirror();
	void showTextMap();
	void draw();
	void findPaths(int x, int y);
	void breakWalls();
	void updateCharacters(int ghostX, int ghostY, int pacmanX, int pacmanY);
	void findStartingPoint();
	void addCharacters(Ghost g, int pacmanRow, int pacmanColumn);
	int getNextWall(int x, int y, int direction);
};

