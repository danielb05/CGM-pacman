#pragma once

/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 4 - Inclusion of lighting effects to the game
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

//#include <GL/freeglut.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"
// #include "libjpeg.h"

//#include "/home/daniel/jpeg-6b/jpeglib.h"

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

#define PACMAN_RADIUS 5
#define GHOST_RADIUS 5
#define FOOD_RADIUS 3

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

// Time constant in millisseconds for the ghost to pass between cells
#define GHOST_VELOCITY 150

// Colors of the Objects
#define WALL_COLOR 0.0, 0.5, 1.0, 1.0
#define FOOD_COLOR 1.0, 0.5, 0.0, 1.0
#define PACMAN_COLOR 1.0, 1.0, 0.0, 1.0
#define GHOST_COLOR 1.0, 1.0, 1.0, 1.0
#define FLOOR_COLOR 0.35, 0.35, 0.25, 1.0


// Movement Direction
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
