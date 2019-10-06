#pragma once

/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 3 - Pacman 3D graphics and texture implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include <GL/freeglut.h>
//#include <GL/glut.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>

#define PI 3.1416

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

//Time constant in millisseconds for the ghost to pass between cells
#define GHOST_VELOCITY 150
