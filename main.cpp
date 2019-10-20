//#include "stdafx.h"

/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 3 - Pacman 3D graphics and texture implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include "constants.h"
#include "map.h"
#include "pacman.h"
#include "ghost.h"
#include "texture.h"

using namespace std;

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 0;
int anglebeta = 50;

//-----------------------------------------------

void PositionObserver(float alpha, float beta, int radi);
void display();
void keyboard(int key, int x, int y);
void idle();
void initiateMap();
void initiateOpenGl(int argc, char *argv[]);
void cameraControl(unsigned char c, int x, int y);
void drawWall(int i, int j);
void drawFood(GLUquadric *quad, int i, int j);
void drawPacman(GLUquadric *quad);
void drawGhost(GLUquadric *quad);
void drawFloor(int i, int j);
void addAmbientLight();
void addSpotLight(char character);

void ReadJPEG(char *filename,unsigned char **image,int *width, int *height);
void LoadTexture(char *filename,int dim);


int WIDTH;
int HEIGHT;

Map map;
Ghost ghost1;
Pacman pacman;
Texture texture;
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

	addAmbientLight();

	int x = map.ROWS - 1;
	int y = map.COLUMNS2 - 1;

	glTranslatef(-(HEIGHT / 2.0), 0, -(WIDTH / 2.0));

	GLUquadric *quad;
	quad = gluNewQuadric();

	gluQuadricDrawStyle(quad, GLU_SILHOUETTE);

	for (int i = 0; i < map.ROWS; i++) {
		for (int j = 0; j < map.COLUMNS2; j++) {

			if (map.mapSurface2[i][j] == FIXEDWALL || map.mapSurface2[i][j] == INNERWALL) {
				
				drawWall(i, j);
			} 
			
			else {
				
				drawFloor(i, j);
			}

			if (map.mapSurface2[i][j] == FOOD) {

				drawFood(quad, i, j);
			}

			if (map.mapSurface2[i][j] == PACMAN) {

				drawPacman(quad);
			}

			if (map.mapSurface2[i][j] == GHOST) {

				drawGhost(quad);
			}
		}
	}

	glutSwapBuffers();
}

void drawWall(int i, int j)
{
	GLfloat material[4] = {1,1,1,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);
	
	glPushMatrix(); //remember current matrix
  
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,0);
	
	// Upper
	glBegin(GL_POLYGON);
	
	glNormal3f(0,1,0);
	glTexCoord2f(0.0,0.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //1
	glTexCoord2f(0.0,1.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(1.0,1.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(1.0,0.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Walls color
	//glColor3f(WALL_COLOR);
	float material2[4] = {WALL_COLOR};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material2);  

	// Front
	glBegin(GL_POLYGON);

	glNormal3f(0,0,1);
	//glTexCoord2f(-4.0,0.0); 
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //4
	//glTexCoord2f(4.0,0.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	//glTexCoord2f(4.0,4.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //2
	//glTexCoord2f(-4.0,4.0);
	glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //1

	glEnd();


	// Back
	glBegin(GL_POLYGON);

	glNormal3f(0,0,-1);
	//glTexCoord2f(-4.0,0.0);
	glVertex3i(j * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	//glTexCoord2f(4.0,0.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //2
	//glTexCoord2f(4.0,4.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //3
	//glTexCoord2f(-4.0,4.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //4

	glEnd();

	// Right
	glBegin(GL_POLYGON);

	glNormal3f(1,0,0);
	//glTexCoord2f(-4.0,0.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	//glTexCoord2f(4.0,0.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
	//glTexCoord2f(4.0,4.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	//glTexCoord2f(-4.0,4.0);
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();

	// Left
	glBegin(GL_POLYGON);

	glNormal3f(-1,0,0);
	//glTexCoord2f(-4.0,0.0);
	glVertex3i(j * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	//glTexCoord2f(4.0,0.0);
	glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
	//glTexCoord2f(4.0,4.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	//glTexCoord2f(-4.0,4.0);
	glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();
	
	glPopMatrix(); //restore matrix

}

void drawFood(GLUquadric *quad, int i, int j)
{
	// Food color
	//glColor3f(FOOD_COLOR);
	float material[4] = {FOOD_COLOR};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);  

	glPushMatrix(); //remember current matrix
	glTranslatef((j * HEIGHT / map.ROWS) + (BLOCKWIDTH / 2), 10, (i * WIDTH / map.COLUMNS2) + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, FOOD_RADIUS, 40, 20);

	glEnd();
	glPopMatrix(); //restore matrix
}

void drawPacman(GLUquadric *quad)
{
	// Pacman color
	//glColor3f(PACMAN_COLOR);
	float material[4] = {PACMAN_COLOR};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);  

	addSpotLight(PACMAN);

	glPushMatrix(); //remember current matrix
	
	glTranslatef(pacman.displayWidth + (BLOCKWIDTH / 2), 10, pacman.displayHeight + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, PACMAN_RADIUS, 50, 20);

	glEnd();
	glPopMatrix(); //restore matrix
}

void drawGhost(GLUquadric *quad)
{
	// Ghost color
	// glColor3f(GHOST_COLOR);

	float material[4] = {GHOST_COLOR};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);  

	addSpotLight(GHOST);
	
	glPushMatrix(); //remember current matrix
	glTranslatef(ghost1.displayWidth + (BLOCKWIDTH / 2), 10, ghost1.displayHeight + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, GHOST_RADIUS, 50, 20);

	glEnd();
	glPopMatrix(); //restore matrix
}

void drawFloor(int i, int j)
{

	// Floor color
	//glColor3f(FLOOR_COLOR);

	float material[4] = {FLOOR_COLOR};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);  

	//  Upper
	glBegin(GL_POLYGON);
	
	// glNormal3f(0,1,0);
	// glVertex3i(0, 0, 0); //1
	// glVertex3i(0, 0, WIDTH); //2
	// glVertex3i(HEIGHT, 0, WIDTH); //3
	// glVertex3i(HEIGHT, 0, 0); //4
	
	glNormal3f(0,1,0);

	glVertex3i(j * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //3
	glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //4

	glEnd();
}

void addAmbientLight() {

	GLint position[4] = {0,0,0,1};
	GLfloat color[4] = {0.1,0.1,0.1,0.5};

	//-- Ambient light

	glLightiv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,color);

	glLightfv(GL_LIGHT0,GL_DIFFUSE,color);
    glLightfv(GL_LIGHT0,GL_SPECULAR,color);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHT0);
}

void addSpotLight(char character) {
	
	GLint position[] = {0, 10, 0, 1};
	GLfloat color[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat direction[] = {0.0, -0.2, 0.0};
	GLfloat cut[] = {20.0};

	if(character == PACMAN){ // PACMAN
		
    	if(pacman.lastDirection==UP){
			
			position[0] = pacman.displayWidth + (BLOCKWIDTH / 2);
			position[2] = pacman.displayHeight + (BLOCKWIDTH / 2) - PACMAN_RADIUS - 1;
			direction[2] = -1.0;
		}
		
    	if(pacman.lastDirection==DOWN){
			
			position[0] = pacman.displayWidth + (BLOCKWIDTH / 2);
			position[2] = pacman.displayHeight + (BLOCKWIDTH / 2) + PACMAN_RADIUS + 1;
			direction[2] = 1.0;
		}
		
    	if(pacman.lastDirection==RIGHT){
			
			position[0] = pacman.displayWidth + (BLOCKWIDTH / 2) + PACMAN_RADIUS + 1;
			position[2] = pacman.displayHeight + (BLOCKWIDTH / 2);
			direction[0] = 1.0;
		}
    	
		if(pacman.lastDirection==LEFT){
			
			position[0] = pacman.displayWidth + (BLOCKWIDTH / 2) - PACMAN_RADIUS - 1;
			position[2] = pacman.displayHeight + (BLOCKWIDTH / 2);
			direction[0] = -1.0;
		}

		glLightiv(GL_LIGHT1,GL_POSITION,position);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,color);
		glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,1.0);
		glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,0.0);
		glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,0.0);
		glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF, cut);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, direction);

		glEnable(GL_LIGHT1);

	}
	else { // GHOST

		if(ghost1.lastDirection==UP){
			
			position[0] = ghost1.displayWidth + (BLOCKWIDTH / 2);
			position[2] = ghost1.displayHeight + (BLOCKWIDTH / 2) - GHOST_RADIUS - 1;
			direction[2] = -1.0;
		}
		
    	if(ghost1.lastDirection==DOWN){
			
			position[0] = ghost1.displayWidth + (BLOCKWIDTH / 2);
			position[2] = ghost1.displayHeight + (BLOCKWIDTH / 2) + GHOST_RADIUS + 1;
			direction[2] = 1.0;
		}
		
    	if(ghost1.lastDirection==RIGHT){
			
			position[0] = ghost1.displayWidth + (BLOCKWIDTH / 2) + GHOST_RADIUS + 1;
			position[2] = ghost1.displayHeight + (BLOCKWIDTH / 2);
			direction[0] = 1.0;
		}
    	
		if(ghost1.lastDirection==LEFT){
			
			position[0] = ghost1.displayWidth + (BLOCKWIDTH / 2) - GHOST_RADIUS - 1;
			position[2] = ghost1.displayHeight + (BLOCKWIDTH / 2);
			direction[0] = -1.0;
		}

		glLightiv(GL_LIGHT2,GL_POSITION,position);
		glLightfv(GL_LIGHT2,GL_DIFFUSE,color);
		glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,1.0);
		glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,0.0);
		glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,0.0);
		glLightfv(GL_LIGHT2,GL_SPOT_CUTOFF, cut);
		glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, direction);

		glEnable(GL_LIGHT2);
	}	
}

void cameraControl(unsigned char c, int x, int y)
{
	int i, j;

	if (c == 'i' && anglebeta <= (90 - 4))
		anglebeta = (anglebeta + 3);
	else if (c == 'k' && anglebeta >= (-90 + 4))
		anglebeta = anglebeta - 3;
	else if (c == 'j')
		anglealpha = (anglealpha + 3) % 360;
	else if (c == 'l')
		anglealpha = (anglealpha - 3 + 360) % 360;

	//cout << "Beta: " << anglebeta << ", Alpha: " << anglealpha <<"\n";
	glutPostRedisplay();
}

void keyboard(int key, int x, int y) {

	if (!ghost1.isMoving) {
		int finalPoint[2] = { ghost1.ghostRow, ghost1.ghostColumn };

		switch (key) {
		case GLUT_KEY_UP:
			//cout << "keyUP\n";
			finalPoint[0] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, UP);
			ghost1.lastDirection = UP;
			break;

		case GLUT_KEY_DOWN:
			//cout << "keyDOWN\n";
			finalPoint[0] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, DOWN);
			ghost1.lastDirection = DOWN;
			break;

		case GLUT_KEY_LEFT:
			//cout << "keyLEFT\n";
			finalPoint[1] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, LEFT);
			ghost1.lastDirection = LEFT;
			break;

		case GLUT_KEY_RIGHT:
			//cout << "keyRIGHT\n";
			finalPoint[1] = map.getNextWall(ghost1.ghostRow, ghost1.ghostColumn, RIGHT);
			ghost1.lastDirection = RIGHT;
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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(cameraControl);
	glutIdleFunc(idle);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, HEIGHT - 1, WIDTH - 1, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.LoadTexture("images/water.jpg",64);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);    
    
    glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	glutMainLoop();
}