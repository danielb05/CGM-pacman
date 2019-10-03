#pragma once


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

	Pacman();
	void addMap(Map m);
	void setPosition(int pacmanRow, int pacmanColumn);
	void nextPosition();
	void startWalk();
	void refreshWalk(long elapsedTime);

private:

	void setVectorPoints();
};

