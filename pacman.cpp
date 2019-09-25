#include <iostream>
#include <string>
#include <cmath>
#include <sstream> 
#include <cstdlib>
#include <ctime>

#include <GL/glut.h>

using namespace std;

#define BLOCKHEIGHT 20
#define BLOCKWIDTH 20
#define MAXROWS 50
#define MAXCOLUMNS 50
#define MINROWS 10
#define MINCOLUMNS 10


void display();
void display2();

int randomDirection(int lastDirection);
int lastDirection = 5;

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
		void showTextMap2();
		void draw();
		void findPaths(int x, int y);
		void breakWalls();
		int randomDirection(int lastDirection);
};

void Map::set_values() {

	bool invalid = true;

	cout << "Please enter the number of rows (min " << MINROWS << ", max " << MAXROWS << "): ";
	cin >> ROWS;

	while (invalid)
	{
		if (ROWS < MINROWS || ROWS > MAXROWS) {
			cout << "Please enter a valid number of rows (min " << MINROWS <<", max " << MAXROWS << "): ";
			cin >> ROWS;
		}
		else
		{
			invalid = false;
		}
	}

	invalid = true;
	
	cout << "\nPlease enter the number of columns (min " << MINCOLUMNS << ", max " << MAXCOLUMNS << "): ";
	cin >> COLUMNS2;

	while (invalid)
	{
		if (COLUMNS2 < MINCOLUMNS || COLUMNS2 > MAXCOLUMNS) {
			cout << "Please enter a valid number of columns (min " << MINCOLUMNS << ", max " << MAXCOLUMNS << "): ";
			cin >> COLUMNS2;
		}
		else
		{
			invalid = false;
		}
	}
	
	rowHalf = (int)floor(ROWS / 2) - 1;

	COLUMNS = ceil(COLUMNS2 / 2);

	columnHalf = (int)COLUMNS - 1;

	mapSurface = new char *[(int)ROWS];//Matrix is now a pointer to an array of 'rows' point

	for (int i = 0; i < ROWS; i++) {

		mapSurface[i] = new char[(int)COLUMNS];		//the ith array is initialized
	}

	initiateMap();
}

void Map::initiateMap() {
	int i, j;
	i = 0;

	while (i < ROWS) {

		j = 0;

		while (j < COLUMNS) {
			mapSurface[i][j] = '1';
			j++;
		}

		i++;
	};
}

void Map::drawBorders() {
	int i, j;
	i = 0;

	while (i < ROWS) {

		j = 0;

		while (j < COLUMNS) {
			if (i == 0 || j == 0 || i == ROWS - 1) {
				mapSurface[i][j] = 'X';
			}
			j++;
		}

		i++;
	};
}

void Map::drawCenter() {

	// To draw the center, draw the following:
	/*
	1 1 0 0 1 1
	1 0 0 0 0 1
	1 1 1 1 1 1
	*/
	// Right to left, from the floor of ROWS/2 -1 y-axis and the floor of COLUMS/2 x-axis ( For odd columns, even need a -1 on the result)

	for (int i = rowHalf; i < rowHalf + 3; i++) { // Position the drawer at the y-axis center starting line and move down
		for (int j = columnHalf; j > columnHalf - 3; j--) { // Position the drawer at the x-axis center and move left
			if (i == rowHalf + 2 || j == columnHalf - 2 || (i == rowHalf && j != columnHalf))
				mapSurface[i][j] = 'X';
			else
				mapSurface[i][j] = ' ';
		}
	}
}

void Map::mirror() {

	mapSurface2 = new char *[(int)ROWS];	//Matrix is now a pointer to an array of 'rows' point

	for (int i = 0; i < ROWS; i++) {

		mapSurface2[i] = new char[(int)COLUMNS2];	//the ith array is initialized
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			mapSurface2[i][j] = mapSurface[i][j];
			mapSurface2[i][(int)COLUMNS2 - j - 1] = mapSurface[i][j];
		}
	}
}

void Map::showTextMap() {

	cout << "\n";

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			cout << mapSurface[i][j];
		}

		cout << "\n";
	}
}

void Map::showTextMap2() {

	cout << "\n";

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS2; j++) {
			cout << mapSurface2[i][j];
		}

		cout << "\n";
	}
}

void Map::findPaths(int x, int y) {

	mapSurface[x][y] = ' ';
	//showTextMap();
	int d = randomDirection(lastDirection);
	
	//North
	if (d == 0) {
		if (x - 1 >= 0) {
			if (mapSurface[x - 1][y] == '1') {
				if(y - 1 >= 0 && mapSurface[x][y-1] == '1')
					mapSurface[x][y - 1] = 'Y';
				if (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
					mapSurface[x][y + 1] = 'Y';
				
				lastDirection = 5;
				findPaths(x - 1, y);
			}
		}		
	}
	//South
	else if (d == 1) {
		if (x + 1 < ROWS) {
			if (mapSurface[x + 1][y] == '1') {
				if (y - 1 >= 0 && mapSurface[x][y - 1] == '1')
					mapSurface[x][y - 1] = 'Y';
				if (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
					mapSurface[x][y + 1] = 'Y';
				
				lastDirection = 5;
				findPaths(x + 1, y);
			}
		}
	}
	//West
	else if (d == 2) {
		if (y - 1 >= 0) {
			if (mapSurface[x][y - 1] == '1') {
				if (x - 1 >= 0 && mapSurface[x - 1][y] == '1')
					mapSurface[x - 1][y] = 'Y';
				if (x + 1 < ROWS && mapSurface[x + 1][y] == '1')
					mapSurface[x + 1][y] = 'Y';
				
				lastDirection = 5;
				findPaths(x, y - 1);
			}
		}
	}
	//East
	else if (d == 3) {
		if (y + 1 < COLUMNS) {
			if (mapSurface[x][y + 1] == '1') {
				if (x - 1 >= 0 && mapSurface[x - 1][y] == '1')
					mapSurface[x - 1][y] = 'Y';
				if (x + 1 < ROWS && mapSurface[x + 1][y] == '1')
					mapSurface[x + 1][y] = 'Y';
				
				lastDirection = 5;
				findPaths(x, y + 1);
			}
		}
	}
	if ((x + 1 < ROWS && mapSurface[x + 1][y] == '1')
		|| (x - 1 >= 0 && mapSurface[x - 1][y] == '1')
		|| (y + 1 < COLUMNS && mapSurface[x][y + 1] == '1')
		|| (y - 1 >= 0 && mapSurface[x][y - 1] == '1')) {
		lastDirection = d;
		findPaths(x, y);
	}
}

void Map::breakWalls() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (mapSurface[i][j] == '1') {
				findPaths(i, j);
			}
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			int count = 0;
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
					}
					else if (mapSurface[i - 1][j] == 'Y') {
						mapSurface[i - 1][j] = ' ';
					}
					if (mapSurface[i][j + 1] == 'Y') {
						mapSurface[i][j + 1] = ' ';
					}
					else if (mapSurface[i][j - 1] == 'Y') {
						mapSurface[i][j - 1] = ' ';
					}
				}
				if (count == 3) {
					if (mapSurface[i + 1][j] == 'Y') {
						mapSurface[i + 1][j] = ' ';
					}
					else if (mapSurface[i][j + 1] == 'Y') {
						mapSurface[i][j + 1] = ' ';
					}
					else if (mapSurface[i - 1][j] == 'Y') {
						mapSurface[i - 1][j] = ' ';
					}
				}
			}
		}
	}
}

void Map::draw() {

	drawBorders();
	drawCenter();
	findPaths(rowHalf-1, columnHalf);
	breakWalls();
	mirror();
	showTextMap2();
}

int Map::randomDirection(int lastDirection) {

	int range = 3 - 0 + 1;
	int num = 0;
	do {
		num = rand() % range;
	} while (num == lastDirection);
	return num;
}

Map map;
int WIDTH;
int HEIGHT;

int main(int argc, char *argv[]) {

	srand(time(0));

	map.set_values();
	map.draw();

	WIDTH = map.COLUMNS2 * BLOCKWIDTH;
	HEIGHT = map.ROWS * BLOCKHEIGHT;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Pacman maze");

	//glutDisplayFunc(display);
	glutDisplayFunc(display2);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

	glutMainLoop();

	return 0;
}

void display2()
{
	int i, j;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25, 0.25, 1.66);

	int x = map.ROWS - 1;
	int y = map.COLUMNS2 - 1;

	for (int i = 0; i < map.ROWS; i++) {
		for (int j = 0; j < map.COLUMNS2; j++) {
			if (map.mapSurface2[x - i][y - j] != ' ') {

				char c = map.mapSurface2[x - i][y - j];

				if (map.mapSurface2[x - i][y - j] == 'X')
					glColor3f(0.8, 0.8, 0.8);
				//else if(map.mapSurface2[x - i][y - j] == 'Y') 
				//	glColor3f(1.8, 1.8, 0.8);
				else if (map.mapSurface2[x - i][y - j] == '1')
					glColor3f(0.8, 1.8, 0.8);
				else
					glColor3f(0.25, 0.25, 1.66);

				glBegin(GL_QUADS);

				//a d
				//b c

				glVertex2i(j*HEIGHT / map.ROWS, i*WIDTH / map.COLUMNS2);
				int ax = j * HEIGHT / map.ROWS;
				int ay = i * WIDTH / map.COLUMNS2;

				glVertex2i(j*HEIGHT / map.ROWS, (i + 1)*WIDTH / map.COLUMNS2);
				int bx = j * HEIGHT / map.ROWS;
				int by = (i + 1)*WIDTH / map.COLUMNS2;

				glVertex2i((j + 1)*HEIGHT / map.ROWS, (i + 1)*WIDTH / map.COLUMNS2);
				int cx = (j + 1)*HEIGHT / map.ROWS;
				int cy = (i + 1)*WIDTH / map.COLUMNS2;

				glVertex2i((j + 1)*HEIGHT / map.ROWS, i*WIDTH / map.COLUMNS2);
				int dx = (j + 1)*HEIGHT / map.ROWS;
				int dy = i * WIDTH / map.COLUMNS2;

				glEnd();
			}
		}
	}

	glutSwapBuffers();

}

void display()
{
	int i, j;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25, 0.25, 1.66);

	int x = map.COLUMNS - 1;
	int y = map.ROWS - 1;

	for (int i = 0; i < map.ROWS; i++) {
		for (int j = 0; j < map.COLUMNS; j++) {
			if (map.mapSurface[y - i][x - j] != ' ') {

				if (map.mapSurface[y - i][x - j] == 'X')
					glColor3f(0.8, 0.8, 0.8);
				else if (map.mapSurface[y - i][x - j] == 'Y')
					glColor3f(0.25, 0.25, 1.66);
				else if (map.mapSurface[y - i][x - j] == '1')
					glColor3f(0.8, 1.8, 0.8);
				else
					glColor3f(0.25, 0.25, 1.66);

				glBegin(GL_QUADS);

				//a d
				//b c

				glVertex2i(j*HEIGHT / map.ROWS, i*WIDTH / map.COLUMNS);
				int ax = j * HEIGHT / map.ROWS;
				int ay = i * WIDTH / map.COLUMNS;

				glVertex2i(j*HEIGHT / map.ROWS, (i + 1)*WIDTH / map.COLUMNS);
				int bx = j * HEIGHT / map.ROWS;
				int by = (i + 1)*WIDTH / map.COLUMNS;

				glVertex2i((j + 1)*HEIGHT / map.ROWS, (i + 1)*WIDTH / map.COLUMNS);
				int cx = (j + 1)*HEIGHT / map.ROWS;
				int cy = (i + 1)*WIDTH / map.COLUMNS;

				glVertex2i((j + 1)*HEIGHT / map.ROWS, i*WIDTH / map.COLUMNS);
				int dx = (j + 1)*HEIGHT / map.ROWS;
				int dy = i * WIDTH / map.COLUMNS;

				glEnd();
			}
		}
	}

	glutSwapBuffers();

}