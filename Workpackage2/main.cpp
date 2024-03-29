//#include "stdafx.h"

/*
03/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 2 - Pacman food and characters implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include <GL/freeglut.h>
//#include <GL/glut.h>
#include <iostream>
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
void keyboard(int key, int x, int y);
void idle();
void initiateMap();
void initiateOpenGl(int argc, char *argv[]);

int WIDTH;
int HEIGHT;

Map map;
Ghost ghost1;
Pacman pacman;
long lastTime = 0;

// Main function
int main(int argc, char *argv[]) {


	initiateMap();

	initiateOpenGl(argc, argv);

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
			if (map.mapSurface2[i][j] == FIXEDWALL || map.mapSurface2[i][j] == INNERWALL) {
				
				// Walls color
				glColor3f(0.25, 0.25, 1.0);

				glBegin(GL_QUADS);

				// Sets the poligon vertices
				/*
				4 3
				1 2
				*/
				glVertex2i(j * HEIGHT / map.ROWS, i * WIDTH / map.COLUMNS2); //1
				glVertex2i(j * HEIGHT / map.ROWS, (i + 1) * WIDTH / map.COLUMNS2); //2
				glVertex2i((j + 1) * HEIGHT / map.ROWS, (i + 1) * WIDTH / map.COLUMNS2); //3
				glVertex2i((j + 1) * HEIGHT / map.ROWS, i * WIDTH / map.COLUMNS2); //4

				glEnd();
			}

			if (map.mapSurface2[i][j] == FOOD) {

				// Food color
				glColor3f(0.35, 0.8, 1.0);
				glBegin(GL_QUADS);

				glVertex2i((j * HEIGHT / map.ROWS) + FOODHEIGHT, (i * WIDTH / map.COLUMNS2) + FOODWIDTH); //1
				glVertex2i((j * HEIGHT / map.ROWS) + FOODHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH); //2
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH); //3
				glVertex2i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, (i * WIDTH / map.COLUMNS2) + FOODWIDTH); //4

				glEnd();
			}
			if (map.mapSurface2[i][j] == PACMAN) {

				// Pacman color
				glColor3f(1.0, 1.0, 0.0);
				glBegin(GL_QUADS);

				glVertex2i(pacman.displayWidth + CHARACTERHEIGHT, pacman.displayHeight + CHARACTERWIDTH); //1
				glVertex2i(pacman.displayWidth + CHARACTERHEIGHT, pacman.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //2
				glVertex2i(pacman.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, pacman.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //3
				glVertex2i(pacman.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, pacman.displayHeight + CHARACTERWIDTH); //4

				glEnd();
			}

			if(map.mapSurface2[i][j] == GHOST){

				// Ghost color
				glColor3f(0.86, 0.86, 0.86);
				glBegin(GL_QUADS);

				glVertex2i(ghost1.displayWidth + CHARACTERHEIGHT, ghost1.displayHeight + CHARACTERWIDTH); //1
				glVertex2i(ghost1.displayWidth + CHARACTERHEIGHT, ghost1.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //2
				glVertex2i(ghost1.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, ghost1.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //3
				glVertex2i(ghost1.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, ghost1.displayHeight + CHARACTERWIDTH); //4

				glEnd();
			}
		}
	}

	glutSwapBuffers();
}

void keyboard(int key, int x, int y) {

	if (!ghost1.isMoving) {
		int finalPoint[2] = { ghost1.ghostRow, ghost1.ghostColumn };

		switch (key) {
		case GLUT_KEY_UP:
			//cout << "keyUP\n";
			finalPoint[0] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, 0);
			break;

		case GLUT_KEY_DOWN:
			//cout << "keyDOWN\n";
			finalPoint[0] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, 1);
			break;

		case GLUT_KEY_LEFT:
			//cout << "keyLEFT\n";
			finalPoint[1] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, 2);
			break;

		case GLUT_KEY_RIGHT:
			//cout << "keyRIGHT\n";
			finalPoint[1] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, 3);
			break;

		default:
			return;
		}

		//cout << "(" << finalPoint[0] << ", " << finalPoint[1] <<")\n";

		ghost1.ghostDestinationRow = finalPoint[0];
		ghost1.ghostDestinationColumn = finalPoint[1];

		ghost1.startWalk();

		glutPostRedisplay();
	}
	
}

void idle() {

	long elapsedTime;

	elapsedTime = glutGet(GLUT_ELAPSED_TIME);

	if (lastTime == 0)
		lastTime = elapsedTime;
	else {

		ghost1.refreshWalk(elapsedTime - lastTime);
		pacman.refreshWalk(elapsedTime - lastTime);
		lastTime = elapsedTime;
	}

	glutPostRedisplay();
}

void initiateMap() {

	srand(time(0));

	map.set_values();
	map.draw();

	pacman.addMap(map);

	ghost1.setPosition(map.rowHalf, map.columnHalf);
	pacman.setPosition(map.startingPoint[0], map.startingPoint[1]);

	map.addCharacters(ghost1, pacman.pacmanRow, pacman.pacmanColumn);
	map.showTextMap();

	WIDTH = map.COLUMNS2 * BLOCKWIDTH;
	HEIGHT = map.ROWS * BLOCKHEIGHT;	
}

void initiateOpenGl(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Pacman maze");

	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutIdleFunc(idle);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, HEIGHT - 1, WIDTH - 1, 0);

	glutMainLoop();
}