#pragma once

/*
03/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 2 - Pacman food and characters implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "next_direction.h"
#include "pacman.h"
#include "ghost.h"

// Define constants for poligon size and map constraints
#define MAXROWS 50
#define MAXCOLUMNS 50
#define MINROWS 10
#define MINCOLUMNS 10

#define FIXEDWALL 'X'
#define INNERWALL 'Y'
#define MOVABLEWALL '1'
#define FOOD 'F'
#define PACMAN 'P'
#define EMPTYSPACE ' '
#define GHOST 'G'

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
	void addCharacters(Ghost g, Pacman p);
	void findStartingPoint();
	int getNextWall(int x, int y, int direction);
};