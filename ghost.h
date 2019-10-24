/*
10/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 4 - Inclusion of lighting effects to the game
Students:
Daniel Vieira Cordeiro
Rafael Câmara Pereira
*/

#pragma once

#include "constants.h"

class Ghost
{
public:
	int ghostRow;
	int ghostColumn;

	int ghostDestinationRow;
	int ghostDestinationColumn;

	int pathDistance;

	float displayWidth;
	float displayHeight;

	float destinationWidth;
	float destinationHeight;

	float velocityRow;
	float velocityColumn;

	long remainingTime;

	bool isMoving;

	int lastDirection;

public:

	Ghost();
	void setPosition(int ghostRow, int ghostColumn);
	void startWalk();
	void refreshWalk(long elapsedTime);

private:
	void setVectorPoints();
};
