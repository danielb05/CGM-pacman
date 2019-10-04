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

#include "constants.h"
#include "map.h"
#include "pacman.h"
#include "ghost.h"

using namespace std;

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta = 0;

//-----------------------------------------------

void PositionObserver(float alpha, float beta, int radi);
void display();
void keyboard(int key, int x, int y);
void idle();
void initiateMap();
void initiateOpenGl(int argc, char *argv[]);
void cameraControl(unsigned char c,int x,int y);

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

void PositionObserver(float alpha, float beta, int radi)
{
	float x, y, z;
	float upx, upy, upz;
	float modul;

	x = (float)radi*cos(alpha * 2 * PI / 360.0)*cos(beta * 2 * PI / 360.0);
	y = (float)radi*sin(beta * 2 * PI / 360.0);
	z = (float)radi*sin(alpha * 2 * PI / 360.0)*cos(beta * 2 * PI / 360.0);

	if (beta>0)
	{
		upx = -x;
		upz = -z;
		upy = (x*x + z * z) / y;
	}
	else if (beta == 0)
	{
		upx = 0;
		upy = 1;
		upz = 0;
	}
	else
	{
		upx = x;
		upz = z;
		upy = -(x*x + z * z) / y;
	}


	modul = sqrt(upx*upx + upy * upy + upz * upz);

	upx = upx / modul;
	upy = upy / modul;
	upz = upz / modul;

	gluLookAt(x, y, z, 0.0, 0.0, 0.0, upx, upy, upz);
}

// Draws the map for OpenGL exhibition
void display() {

	int i, j;

	// Path color
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	PositionObserver(anglealpha, anglebeta, 450);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH * 0.7, WIDTH*0.7, -HEIGHT * 0.7, HEIGHT*0.7, 10, 2000);

	glMatrixMode(GL_MODELVIEW);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	int x = map.ROWS - 1;
	int y = map.COLUMNS2 - 1;
glTranslatef(-(HEIGHT/2.0), 0, -(WIDTH/2.0));
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
				glVertex3i(j * HEIGHT / map.ROWS, 0,  i * WIDTH / map.COLUMNS2); //1
				glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
				glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //3
				glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //4

				glEnd();
			}

			if (map.mapSurface2[i][j] == FOOD) {

				// Food color
				glColor3f(0.35, 0.8, 1.0);
				glBegin(GL_QUADS);

				glVertex3i((j * HEIGHT / map.ROWS) + FOODHEIGHT, 0, (i * WIDTH / map.COLUMNS2) + FOODWIDTH); //1
				glVertex3i((j * HEIGHT / map.ROWS) + FOODHEIGHT, 0, ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH); //2
				glVertex3i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, 0,  ((i + 1) * WIDTH / map.COLUMNS2) - FOODWIDTH); //3
				glVertex3i(((j + 1) * HEIGHT / map.ROWS) - FOODHEIGHT, 0, (i * WIDTH / map.COLUMNS2) + FOODWIDTH); //4

				glEnd();
			}
			if (map.mapSurface2[i][j] == PACMAN) {

				// Pacman color
				glColor3f(1.0, 1.0, 0.0);
				
				
				GLUquadric *quad;
				quad = gluNewQuadric();

				glPushMatrix(); //remember current matrix
				glTranslatef(pacman.displayWidth + (BLOCKWIDTH/2), 0, pacman.displayHeight + (BLOCKWIDTH/2));
				glBegin(GL_QUADS);		
				
				gluSphere(quad,5,50,20);

				glEnd();
				glPopMatrix(); //restore matrix
			}

			if(map.mapSurface2[i][j] == GHOST){

				// Ghost color
				glColor3f(0.86, 0.86, 0.86);
				glBegin(GL_QUADS);

				glVertex3i(ghost1.displayWidth + CHARACTERHEIGHT, 0, ghost1.displayHeight + CHARACTERWIDTH); //1
				glVertex3i(ghost1.displayWidth + CHARACTERHEIGHT, 0, ghost1.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //2
				glVertex3i(ghost1.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, 0, ghost1.displayHeight + BLOCKHEIGHT - CHARACTERWIDTH); //3
				glVertex3i(ghost1.displayWidth + BLOCKWIDTH - CHARACTERHEIGHT, 0, ghost1.displayHeight + CHARACTERWIDTH); //4

				glEnd();
			}
		}
	}

	glutSwapBuffers();
}

void cameraControl(unsigned char c,int x,int y)
{
  int i,j;

  if (c=='i' && anglebeta<=(90-4))
    anglebeta=(anglebeta+3);
  else if (c=='k' && anglebeta>=(-90+4))
    anglebeta=anglebeta-3;
  else if (c=='j')
    anglealpha=(anglealpha+3)%360;
  else if (c=='l')
    anglealpha=(anglealpha-3+360)%360;

  glutPostRedisplay();
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

		if (ghost1.ghostRow == pacman.pacmanRow && ghost1.ghostColumn == pacman.pacmanColumn) {

			pacman.displayHeight = -500;
			pacman.displayWidth = -500;
			pacman.isMoving = false;
		}

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

	anglealpha = 90;
	anglebeta = 30;
}

void initiateOpenGl(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Pacman maze");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);			
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(cameraControl);
	glutIdleFunc(idle);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, HEIGHT - 1, WIDTH - 1, 0);

	glutMainLoop();
}