//#include "stdafx.h"


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
