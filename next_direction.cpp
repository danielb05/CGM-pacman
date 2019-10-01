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

#include "next_direction.h"

using namespace std;

// Sorts the next direction of the corridor
int NextDirection::randomize() {

	int range = 4;
	int num;

	do {

		num = rand() % range;
	} while (visitedDirection[num]);

	visitedDirection[num] = true;

	return num;
}

// Sorts the next direction of the corridor
void NextDirection::startVisiting() {

	visitedDirection[0] = false;
	visitedDirection[1] = false;
	visitedDirection[2] = false;
	visitedDirection[3] = false;
}
