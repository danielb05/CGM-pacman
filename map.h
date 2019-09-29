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
#include "next_direction.h"

// Define constants for poligon size and map constraints
#define MAXROWS 50
#define MAXCOLUMNS 50
#define MINROWS 10
#define MINCOLUMNS 10

class Map {

	public:
		float COLUMNS, ROWS, COLUMNS2;
		char** mapSurface;
		char** mapSurface2;
		int rowHalf;
		int columnHalf;

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
};