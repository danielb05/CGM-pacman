//#include "stdafx.h"

/*
03/10/2019
Universitat de Lleida
Computer Graphics and Multimedia
Task 2 - Pacman food and characters implementation
Students:
Daniel Vieira Cordeiro
Rafael C�mara Pereira
*/

#include "pacman.h"

using namespace std;

Pacman::Pacman() {

	pacmanRow = 0;
	pacmanColumn = 0;
	pacmanDestinationRow = 0;
	pacmanDestinationColumn = 0;
	pathDistance = 0;
	isMoving = false;
	displayWidth = 0.0;
	displayHeight = 0.0;
	destinationWidth = 0.0;
	destinationHeight = 0.0;
	velocityRow = 0.0;
	velocityColumn = 0.0;
	remainingTime = 0.0;
}

void Pacman::addMap(Map m) {
	map = m;
}

void Pacman::setPosition(int pacmanRow, int pacmanColumn)
{
	this->pacmanRow = pacmanRow;
	this->pacmanColumn = pacmanColumn;
	displayHeight = pacmanRow * 20;
	displayWidth = pacmanColumn * 20;

	nextPosition();
}

// Sorts the next direction of Pacman
void Pacman::nextPosition() {

	bool finding = true;
	int direction;
	NextDirection next;
	next.startVisiting();
	direction = lastDirection;
	
	// next direction completely random
	//direction = next.randomize();

	do {		

		// Choose the next block to be digged according to the random direction in 'direction'
		switch (direction) {

			//North
		case 0:
			// If the north is selected, sets the sided cells as FIXED walls and generates the north corridor
			if (pacmanRow - 1 > 0) {
				if (map.mapSurface2[pacmanRow - 1][pacmanColumn] == FOOD || map.mapSurface2[pacmanRow - 1][pacmanColumn] == EMPTYSPACE) {
					map.mapSurface2[pacmanRow][pacmanColumn] = EMPTYSPACE;
					pacmanDestinationRow = pacmanRow - 1;
					pacmanDestinationColumn = pacmanColumn;
					finding = false;
					lastDirection = direction;
				}
				else 
				{
					direction = next.randomize();
				}
			}
			else
			{
				direction = next.randomize();
			}
			break;

			//South
		case 1:
			// If the south is selected, sets the sided cells as FIXED walls and generates the south corridor
			if (pacmanRow + 1 < map.ROWS - 1) {
				if (map.mapSurface2[pacmanRow + 1][pacmanColumn] == FOOD || map.mapSurface2[pacmanRow + 1][pacmanColumn] == EMPTYSPACE) {
					map.mapSurface2[pacmanRow][pacmanColumn] = EMPTYSPACE;
					pacmanDestinationRow = pacmanRow + 1;
					pacmanDestinationColumn = pacmanColumn;
					finding = false;					
					lastDirection = direction;
				}
				else
				{
					direction = next.randomize();
				}
			}
			else
			{
				direction = next.randomize();
			}
			break;

			//West
		case 2:
			// If the west is selected, sets the upper/lower cells as FIXED walls and generates the west corridor
			if (pacmanColumn - 1 > 0) {
				char c = map.mapSurface2[pacmanRow][pacmanColumn - 1];
				if (map.mapSurface2[pacmanRow][pacmanColumn - 1] == FOOD || map.mapSurface2[pacmanRow][pacmanColumn - 1] == EMPTYSPACE) {
					map.mapSurface2[pacmanRow][pacmanColumn] = EMPTYSPACE;
					pacmanDestinationRow = pacmanRow;
					pacmanDestinationColumn = pacmanColumn - 1;
					finding = false;
					lastDirection = direction;
				}
				else
				{
					direction = next.randomize();
				}
			}
			else
			{
				direction = next.randomize();
			}
			break;

			//East
		case 3:
			// If the east is selected, sets the upper/lower cells as FIXED walls and generates the east corridor
			if (pacmanColumn + 1 < map.COLUMNS2) {
				if (map.mapSurface2[pacmanRow][pacmanColumn + 1] == FOOD || map.mapSurface2[pacmanRow][pacmanColumn + 1] == EMPTYSPACE) {
					map.mapSurface2[pacmanRow][pacmanColumn] = EMPTYSPACE;
					pacmanDestinationRow = pacmanRow;
					pacmanDestinationColumn = pacmanColumn + 1;
					finding = false;
					lastDirection = direction;
				}
				else
				{
					direction = next.randomize();
				}
			}
			else
			{
				direction = next.randomize();
			}
			break;
		}
	
	// Verify if pacman has found a moveable spot yet
	} while (finding);

	startWalk();
}

//--------------

void Pacman::startWalk() {

	setVectorPoints();

	velocityRow = (destinationHeight - displayHeight) / (pathDistance * GHOST_VELOCITY);
	velocityColumn = (destinationWidth - displayWidth) / (pathDistance * GHOST_VELOCITY);

	isMoving = true;
	remainingTime = pathDistance * GHOST_VELOCITY;
}

void Pacman::refreshWalk(long elapsedTime) {

	if (isMoving) {
		if (elapsedTime < remainingTime) {

			displayHeight += velocityRow * elapsedTime;
			displayWidth += velocityColumn * elapsedTime;
			remainingTime -= elapsedTime;
		}
		else if (elapsedTime >= remainingTime) {

			displayHeight += velocityRow * remainingTime;
			displayWidth += velocityColumn * remainingTime;
			pacmanRow = pacmanDestinationRow;
			pacmanColumn = pacmanDestinationColumn;
			isMoving = false;
			nextPosition();
		}
	}
}

void Pacman::setVectorPoints() {

	displayHeight = pacmanRow * 20;
	displayWidth = pacmanColumn * 20;

	destinationHeight = pacmanDestinationRow * 20;
	destinationWidth = pacmanDestinationColumn * 20;

	if (pacmanDestinationRow > pacmanRow)
		pathDistance = (pacmanDestinationRow - pacmanRow);
	else
		pathDistance = (pacmanRow - pacmanDestinationRow);

	if (pacmanDestinationColumn > pacmanColumn)
		pathDistance += (pacmanDestinationColumn - pacmanColumn);
	else
		pathDistance += (pacmanColumn - pacmanDestinationColumn);
}