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

//#include "/home/daniel/jpeg-6b/jpeglib.h"

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
void cameraControl(unsigned char c, int x, int y);
void drawWall(int i, int j);
void drawFood(GLUquadric *quad, int i, int j);
void drawPacman(GLUquadric *quad);
void drawGhost(GLUquadric *quad);

void ReadJPEG(char *filename,unsigned char **image,int *width, int *height);
void LoadTexture(char *filename,int dim);


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

	glTranslatef(-(HEIGHT / 2.0), 0, -(WIDTH / 2.0));

	GLUquadric *quad;
	quad = gluNewQuadric();

	gluQuadricDrawStyle(quad, GLU_SILHOUETTE);

	for (int i = 0; i < map.ROWS; i++) {
		for (int j = 0; j < map.COLUMNS2; j++) {
			if (map.mapSurface2[i][j] == FIXEDWALL || map.mapSurface2[i][j] == INNERWALL) {
				
				drawWall(i, j);
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
	// Walls color
	//glColor3f(WALL_COLOR);

	glBindTexture(GL_TEXTURE_2D,0);
	
	// Upper
	glBegin(GL_POLYGON);

	glTexCoord2f(-4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //1
	glTexCoord2f(4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(-4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();

	//glColor3f(1.00, 0.25, 0.25);
	// Front
	glBegin(GL_POLYGON);

	glTexCoord2f(-4.0,0.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //4
	glTexCoord2f(4.0,0.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(4.0,4.0); glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(-4.0,4.0); glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //1

	glEnd();

	//glColor3f(0.25, 1.00, 0.25);
	// Back
	glBegin(GL_POLYGON);

	glTexCoord2f(-4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	glTexCoord2f(4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(-4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //4

	glEnd();

	//glColor3f(0.6, 0.6, 0.25);
	// Right
	glBegin(GL_POLYGON);

	glTexCoord2f(-4.0,0.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(4.0,0.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	glTexCoord2f(-4.0,4.0); glVertex3i((j + 1) * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();

	//glColor3f(0.6, 0.25, 0.6);
	// Left
	glBegin(GL_POLYGON);

	glTexCoord2f(-4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 0, i * WIDTH / map.COLUMNS2); //1
	glTexCoord2f(4.0,0.0); glVertex3i(j * HEIGHT / map.ROWS, 0, (i + 1) * WIDTH / map.COLUMNS2); //2
	glTexCoord2f(4.0,4.0); glVertex3i(j * HEIGHT / map.ROWS, 15, (i + 1) * WIDTH / map.COLUMNS2); //3
	glTexCoord2f(-4.0,4.0); glVertex3i(j * HEIGHT / map.ROWS, 15, i * WIDTH / map.COLUMNS2); //4

	glEnd();
}

void drawFood(GLUquadric *quad, int i, int j)
{
	// Food color
	glColor3f(FOOD_COLOR);

	glPushMatrix(); //remember current matrix
	glTranslatef((j * HEIGHT / map.ROWS) + (BLOCKWIDTH / 2), 10, (i * WIDTH / map.COLUMNS2) + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, 3, 40, 20);

	glEnd();
	glPopMatrix(); //restore matrix
}

void drawPacman(GLUquadric *quad)
{
	// Pacman color
	glColor3f(PACMAN_COLOR);

	glPushMatrix(); //remember current matrix
	glTranslatef(pacman.displayWidth + (BLOCKWIDTH / 2), 10, pacman.displayHeight + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, 5, 50, 20);

	glEnd();
	glPopMatrix(); //restore matrix
}

void drawGhost(GLUquadric *quad)
{
	// Ghost color
	glColor3f(GHOST_COLOR);

	glPushMatrix(); //remember current matrix
	glTranslatef(ghost1.displayWidth + (BLOCKWIDTH / 2), 10, ghost1.displayHeight + (BLOCKWIDTH / 2));
	glBegin(GL_POLYGON);

	gluSphere(quad, 5, 50, 20);

	glEnd();
	glPopMatrix(); //restore matrix
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

	glBindTexture(GL_TEXTURE_2D, 0);

	LoadTexture("pared.jpg",64);

	glutMainLoop();
}

/*--------------------------------------------------------/
 Code for adding textures
/--------------------------------------------------------*/
void ReadJPEG(char *filename,unsigned char **image,int *width, int *height)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE * infile;
  unsigned char **buffer;
  int i,j;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);


  if ((infile = fopen(filename, "rb")) == NULL) {
    printf("Unable to open file %s\n",filename);
    exit(1);
  }

  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_calc_output_dimensions(&cinfo);
  jpeg_start_decompress(&cinfo);

  *width = cinfo.output_width;
  *height  = cinfo.output_height;


  *image=(unsigned char*)malloc(cinfo.output_width*cinfo.output_height*cinfo.output_components);

  buffer=(unsigned char **)malloc(1*sizeof(unsigned char **));
  buffer[0]=(unsigned char *)malloc(cinfo.output_width*cinfo.output_components);


  i=0;
  while (cinfo.output_scanline < cinfo.output_height) {
    jpeg_read_scanlines(&cinfo, buffer, 1);

    for(j=0;j<cinfo.output_width*cinfo.output_components;j++)
      {
	(*image)[i]=buffer[0][j];
	i++;
      }   

    }

  free(buffer);
  jpeg_finish_decompress(&cinfo);
} 

void LoadTexture(char *filename,int dim)
{
  unsigned char *buffer;
  unsigned char *buffer2;
  int width,height;
  long i,j;
  long k,h;

  ReadJPEG(filename,&buffer,&width,&height);

  buffer2=(unsigned char*)malloc(dim*dim*3);

  //-- The texture pattern is subsampled so that its dimensions become dim x dim --
  for(i=0;i<dim;i++)
    for(j=0;j<dim;j++)
      {
	k=i*height/dim;
	h=j*width/dim;
	
	buffer2[3*(i*dim+j)]=buffer[3*(k*width +h)];
	buffer2[3*(i*dim+j)+1]=buffer[3*(k*width +h)+1];
	buffer2[3*(i*dim+j)+2]=buffer[3*(k*width +h)+2];

      }

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dim,dim,0,GL_RGB,GL_UNSIGNED_BYTE,buffer2);

  free(buffer);
  free(buffer2);
}
