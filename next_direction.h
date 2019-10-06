/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 3 - Pacman 3D graphics and texture implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#pragma once

#include "constants.h"

class NextDirection {

public:
	// Positions: 0 = North, 1 = South, 2 = West, 3 = East
	bool visitedDirection[4];
	int randomize();
	void startVisiting();
};