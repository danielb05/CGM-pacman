/*
03/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 2 - Pacman food and characters implementation
Students:
Daniel Vieira Cordeiro
Rafael C�mara Pereira
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

public:

	Ghost();
	void setPosition(int ghostRow, int ghostColumn);
	void startWalk();
	void refreshWalk(long elapsedTime);

private:
	void setVectorPoints();
};
