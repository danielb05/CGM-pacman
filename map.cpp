/*
03/10/2019

Universitat de Lleida
Computer Graphics and Multimedia

Task 2 - Pacman food and characters implementation

Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira

*/

#include "map.h"

using namespace std;

// Gets the values for number of lines and columns
void Map::set_values() {

	bool invalid = true;

	do {

		cout << "Please enter a valid number of rows (min " << MINROWS << ", max " << MAXROWS << "): ";
		cin >> ROWS;

		if (ROWS >= MINROWS && ROWS <= MAXROWS)
			invalid = false;
	}while (invalid);

	invalid = true;

	do {

		cout << "Please enter a valid number of columns (min " << MINCOLUMNS << ", max " << MAXCOLUMNS << "): ";
		cin >> COLUMNS2;

		if (COLUMNS2 >= MINCOLUMNS && COLUMNS2 <= MAXCOLUMNS)
			invalid = false;
	}while (invalid);
	
	// Sets the variables to draw half map, since the map is mirrored
	rowHalf = (int)floor(ROWS / 2) - 1;
	COLUMNS = ceil(COLUMNS2 / 2);
	columnHalf = (int)COLUMNS - 1;

	// Creates a matrix corresponding to half map 
	mapSurface = new char *[(int)ROWS]; //Matrix is now a pointer to an array of 'rows' point

	for (int i = 0; i < ROWS; i++) {

		mapSurface[i] = new char[(int)COLUMNS];		//the ith array is initialized
	}

	initiateMap();
}

// Sets the map to walls
void Map::initiateMap() {

	int j;

	for (int i = 0; i < ROWS; i++) {

		j = 0;

		while (j < COLUMNS) {

			mapSurface[i][j] = '1';
			j++;
		}
	}
}

// Draws the border as FIXED walls
void Map::drawBorders() {

	int j;

	for (int i = 0; i < ROWS; i++) {

		j = 0;

		while (j < COLUMNS) {

			if (i == 0 || j == 0 || i == ROWS - 1)
				mapSurface[i][j] = 'X';
			else
				j = COLUMNS;

			j++;
		}
	}
}

// Draws the center as FIXED walls/corridors
void Map::drawCenter() {

	// To draw the center, draw the following:
	/*
	1 1 0 0 1 1
	1 0 0 0 0 1
	1 0 0 0 0 1
	1 1 1 1 1 1
	*/
	// Right to left, from the floor of ROWS/2 -1 y-axis and the floor of COLUMS/2 x-axis ( For odd columns, even need a -1 on the result)

	for (int i = rowHalf - 1; i < rowHalf + 3; i++) { // Position the drawer at the y-axis center starting line and move down
		for (int j = columnHalf; j > columnHalf - 3; j--) { // Position the drawer at the x-axis center and move left
			if (i == rowHalf + 2 || j == columnHalf - 2 || (i == rowHalf - 1 && j != columnHalf))
				mapSurface[i][j] = 'X';
			else
				mapSurface[i][j] = ' ';
		}
	}
}

// Reflects the left size on the right
void Map::mirror() {

	mapSurface2 = new char *[(int)ROWS]; //Matrix is now a pointer to an array of 'rows' point

	for (int i = 0; i < ROWS; i++) {

		mapSurface2[i] = new char[(int)COLUMNS2]; //the ith array is initialized
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {

			mapSurface2[i][j] = mapSurface[i][j];
			mapSurface2[i][(int)COLUMNS2 - j - 1] = mapSurface[i][j];
		}
	}
}

// Shows the map on terminal output
void Map::showTextMap() {

	cout << "\n";

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS2; j++) {
			cout << mapSurface2[i][j];
		}

		cout << "\n";
	}
}

// Dig the valid way
void Map::findPaths(int x, int y) {

	int direction;
	NextDirection next;
	
	// Sets the current position to a corridor cell
	mapSurface[x][y] = ' ';

	// Randomically selects one way to continue
	next.startVisiting();
	
	do{
		
		direction = next.randomize();
		// Choose the next block to be digged according to the random direction in 'direction'
		switch (direction) {
		
		//North
		case 0:
			// If the north is selected, sets the sided cells as FIXED walls and generates the north corridor
			if (x - 1 > 0) {
				if (mapSurface[x - 1][y] == '1') {
					if (y - 1 > 0 && mapSurface[x][y - 1] == '1')
						mapSurface[x][y - 1] = 'Y';
					if (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
						mapSurface[x][y + 1] = 'Y';

					findPaths(x - 1, y);
				}
			}
			break;
		
		//South
		case 1:
			// If the south is selected, sets the sided cells as FIXED walls and generates the south corridor
			if (x + 1 < ROWS - 1) {
				if (mapSurface[x + 1][y] == '1') {
					if (y - 1 > 0 && mapSurface[x][y - 1] == '1')
						mapSurface[x][y - 1] = 'Y';
					if (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
						mapSurface[x][y + 1] = 'Y';

					findPaths(x + 1, y);
				}
			}
			break;
			
		//West
		case 2:
			// If the west is selected, sets the upper/lower cells as FIXED walls and generates the west corridor
			if (y - 1 > 0) {
				if (mapSurface[x][y - 1] == '1') {
					if (x - 1 > 0 && mapSurface[x - 1][y] == '1')
						mapSurface[x - 1][y] = 'Y';
					if (x + 1 < ROWS - 1 && mapSurface[x + 1][y] == '1')
						mapSurface[x + 1][y] = 'Y';

					findPaths(x, y - 1);
				}
			}
			break;
			
		//East
		case 3:
			// If the east is selected, sets the upper/lower cells as FIXED walls and generates the east corridor
			if (y + 1 < COLUMNS) {
				if (mapSurface[x][y + 1] == '1') {
					if (x - 1 > 0 && mapSurface[x - 1][y] == '1')
						mapSurface[x - 1][y] = 'Y';
					if (x + 1 < ROWS - 1 && mapSurface[x + 1][y] == '1')
						mapSurface[x + 1][y] = 'Y';

					findPaths(x, y + 1);
				}
			}
			break;
		}
	// Verify if there's yet a neghbor with a non-fixed wall
	}while((x + 1 < ROWS && mapSurface[x + 1][y] == '1')
		|| (x - 1 >= 0 && mapSurface[x - 1][y] == '1')
		|| (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
		|| (y - 1 >= 0 && mapSurface[x][y - 1] == '1'));
}

// Used to find and eliminate unreachable areas on the map
void Map::breakWalls() {

	// Looks for non-fixed walls to convert
	for (int i = 1; i < ROWS - 1; i++) {
		for (int j = 1; j < COLUMNS; j++) {
			if (mapSurface[i][j] == '1')
				findPaths(i, j);
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			int count = 0;

			// Verify if the cell is isolated, if so, remove 1 or 2 walls from the neighbours
			if (mapSurface[i][j] == ' ') {
				if (mapSurface[i + 1][j] != ' ') {

					count++;
				}
				if (mapSurface[i - 1][j] != ' ') {

					count++;
				}
				if (mapSurface[i][j + 1] != ' ') {

					count++;
				}
				if (mapSurface[i][j - 1] != ' ') {

					count++;
				}

				if (count == 4) {
					if (mapSurface[i + 1][j] == 'Y') {

						mapSurface[i + 1][j] = ' ';
					} else if (mapSurface[i - 1][j] == 'Y') {

						mapSurface[i - 1][j] = ' ';
					} if (mapSurface[i][j + 1] == 'Y') {

						mapSurface[i][j + 1] = ' ';
					} else if (mapSurface[i][j - 1] == 'Y') {

						mapSurface[i][j - 1] = ' ';
					}
				}
				
				if (count == 3) {
					if (mapSurface[i + 1][j] == 'Y') {

						mapSurface[i + 1][j] = ' ';
					} else if (mapSurface[i][j + 1] == 'Y') {

						mapSurface[i][j + 1] = ' ';
					} else if (mapSurface[i - 1][j] == 'Y') {

						mapSurface[i - 1][j] = ' ';
					}
				}
			}
		}
	}
}

// Calls the necessary functions (in the correct order) in order to ramdomly generate a map 
void Map::draw() {

	drawBorders();
	drawCenter();
	findPaths(rowHalf-1, columnHalf);
	breakWalls();
	mirror();
	showTextMap();
}