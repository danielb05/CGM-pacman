#pragma once

/*
03/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 2 - Pacman food and characters implementation
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#include <cmath>
#include <cstdlib>
#include "next_direction.h"
#include "map.h"

class Pacman {

public:

	int pacmanRow;
	int pacmanColumn;
	int lastDirection;

	int pacmanDestinationRow;
	int pacmanDestinationColumn;

	int pathDistance;

	float displayWidth;
	float displayHeight;

	float destinationWidth;
	float destinationHeight;

	float velocityRow;
	float velocityColumn;

	long remainingTime;

	bool isMoving;

	Map map;

public:

	Pacman(Map m);
	void setPosition(int pacmanRow, int pacmanColumn);
	void nextPosition();
	void startWalk();
	void refreshWalk(long elapsedTime);

private:

	void setVectorPoints();
};

