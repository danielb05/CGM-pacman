/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 3 - Pacman 3D graphics and texture implementation
Students:
Daniel Vieira Cordeiro
Rafael C�mara Pereira
*/

#pragma once

#include "constants.h"
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

	Pacman();
	void addMap(Map m);
	void setPosition(int pacmanRow, int pacmanColumn);
	void nextPosition();
	void startWalk();
	void refreshWalk(long elapsedTime);

private:

	void setVectorPoints();
};

