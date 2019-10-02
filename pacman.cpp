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

#include "pacman.h"

// Sorts the next direction of the corridor
//void Pacman::born(Map map) {
//
//	do {
//		pacmanPosition[0] = rand() % (map.ROWS - 2);
//		pacmanPosition[1] = rand() % (map.COLUMNS2 - 2);
//	} while (map.mapSurface[pacmanPosition[0] + 1][pacmanPosition[1] + 1] != FOOD);
//
//	//nao funciona, acho que tem que fazer um setter em map	
//	map.mapSurface[pacmanPosition[0]][pacmanPosition[1]] = PACMAN;
//
//	/*
//	int range = 4;
//	int num;
//	do {
//	num = rand() % range;
//	} while (visitedDirection[num]);
//	visitedDirection[num] = true;
//
//	return num;
//	*/
//}

Pacman::Pacman(int pacmanRow, int pacmanColumn)
{
	this->pacmanRow = pacmanRow;
	this->pacmanColumn = pacmanColumn;
}

// Sorts the next direction of the corridor
void Pacman::walk() {
	/*
	visitedDirection[0] = false;
	visitedDirection[1] = false;
	visitedDirection[2] = false;
	visitedDirection[3] = false;
	*/
}