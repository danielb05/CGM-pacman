#include "stdafx.h"

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
//#include <GL/freeglut.h>
#include <GL/glut.h>
#include <ctime>
#include "map.h"
#include "pacman.h"
#include "ghost.h"

using namespace std;

// Define constants for poligon size and map constraints
#define BLOCKHEIGHT 20
#define BLOCKWIDTH 20

/*
In the case of food the size considered will be:

- Height: (BLOCKHEIGHT - FOODHEIGHT) / 2
- Width:  (BLOCKWIDTH - FOODWIDTH) / 2

*/
#define FOODHEIGHT 7
#define FOODWIDTH 7

/*
In the case of characters the size considered will be:

- Height: (BLOCKHEIGHT - CHARACTERHEIGHT) / 2
- Width:  (BLOCKWIDTH - CHARACTERWIDTH) / 2

*/
#define CHARACTERHEIGHT 4
#define CHARACTERWIDTH 4

void display();

int WIDTH;
int HEIGHT;

Map map;


// Main function
int main(int argc, char *argv[]) {

	srand(time(0));

	map.set_values();
	map.draw();
	Ghost ghost1(map.rowHalf, map.columnHalf);
	Pacman pacman(map.startingPoint[0], map.startingPoint[1]);

	map.addCharacters(ghost1, pacman);
	

	WIDTH = map.COLUMNS2 * BLOCKWIDTH;
	HEIGHT = map.ROWS * BLOCKHEIGHT;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Pacman maze");

	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WIDTH - 1, 0, HEIGHT - 1);

	glutMainLoop();

	return 0;
}

// Draws the map for OpenGL exhibition
void display() {

	int i, j;

	// Path color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	int x = map.ROWS - 1;
	int y = map.COLUMNS2 - 1;

	for (int i = 0; i < map.ROWS; i++) {
		for (int j = 0; j < map.COLUMNS2; j++) {
			if (map.mapSurface2[x - i][y - j] == FIXEDWALL || map.mapSurface2[x - i][y - j] == INNERWALL) {
				// Walls color
				glColor3f(0.25, 0.25, 1.0);
				char c = map.mapSurface2[x - i][y - j];

				glBegin(GL_QUADS);

				// Sets the poligon vertices
				glVertex2i(j * HEIGHT / map.ROWS, i * WIDTH / map.COLUMNS2);
				glVertex2i(j * HEIGHT / map.ROWS, (i + 1) * WIDTH / map.COLUMNS2);
				glVertex2i((j + 1) * HEIGHT / map.ROWS, (i + 1) * WIDTH / map.COLUMNS2);
				glVertex2i((j + 1) * HEIGHT / map.ROWS, i * WIDTH / map.COLUMNS2);

				glEnd();
			}

			if (map.mapSurface2[x - i][y - j] == FOOD) {

				// Food color
				glColor3f(0.35, 0.8, 1.0);
				char c = map.mapSurface2[x - i][y - j];

				glBegin(GL_QUADS);

				// Sets the poligon vertices
				/*
				4 3
				1 2
				*/
				glVertex2i((j * HEIGHT / map.ROWS) + FOODHEIGHT, (i * WIDTH / map.COLUMNS2) + FOODWIDTH);
				glVertex2i((j * HEIGHT / map.ROWS) + FOODHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH);
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH);
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, (i * WIDTH / map.COLUMNS2) + FOODWIDTH);

				glEnd();
			}
			if (map.mapSurface2[x - i][y - j] == PACMAN || map.mapSurface2[x - i][y - j] == GHOST) {
				
				if (map.mapSurface2[x - i][y - j] == PACMAN) {
					// Pacman color
					glColor3f(1.0, 1.0, 0.0);
				}
				else {
					glColor3f(0.86, 0.86, 0.86);
				}

				char c = map.mapSurface2[x - i][y - j];

				glBegin(GL_QUADS);

				// Sets the poligon vertices
				glVertex2i((j * HEIGHT / map.ROWS) + CHARACTERHEIGHT, (i * WIDTH / map.COLUMNS2) + CHARACTERWIDTH);
				glVertex2i((j * HEIGHT / map.ROWS) + CHARACTERHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - CHARACTERWIDTH);
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - CHARACTERHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - CHARACTERWIDTH);
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - CHARACTERHEIGHT, (i * WIDTH / map.COLUMNS2) + CHARACTERWIDTH);

				glEnd();
			}
		}
	}

	glutSwapBuffers();
}