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

#include "ghost.h"

Ghost::Ghost() {
	ghostRow = 0;
	ghostColumn = 0;
	ghostDestinationRow = 0;
	ghostDestinationColumn = 0;
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

void Ghost::setPosition(int ghostRow, int ghostColumn) {
	this->ghostRow = ghostRow;
	this->ghostColumn = ghostColumn;
	displayHeight = ghostRow * 20;
	displayWidth = ghostColumn * 20;
}

void Ghost::startWalk() {

	setVectorPoints();

	velocityRow = (destinationHeight - displayHeight) / (pathDistance * GHOST_VELOCITY);
	velocityColumn = (destinationWidth - displayWidth) / (pathDistance * GHOST_VELOCITY);

	isMoving = true;
	remainingTime = pathDistance * GHOST_VELOCITY;
}

void Ghost::refreshWalk(long elapsedTime) {

	if (isMoving)
		if (elapsedTime < remainingTime) {

			displayHeight += velocityRow * elapsedTime;
			displayWidth += velocityColumn * elapsedTime;
			remainingTime -= elapsedTime;
		}
		else if (elapsedTime >= remainingTime) {

			displayHeight += velocityRow * remainingTime;
			displayWidth += velocityColumn * remainingTime;
			ghostRow = ghostDestinationRow;
			ghostColumn = ghostDestinationColumn;
			isMoving = false;
		}
}

void Ghost::setVectorPoints() {

	displayHeight = ghostRow * 20;
	displayWidth = ghostColumn * 20;

	destinationHeight = ghostDestinationRow * 20;
	destinationWidth = ghostDestinationColumn * 20;

	pathDistance = 0;
	
	if (ghostDestinationRow > ghostRow)
		pathDistance = (ghostDestinationRow - ghostRow);
	else if(ghostDestinationRow < ghostRow)
		pathDistance = (ghostRow - ghostDestinationRow);

	if (ghostDestinationColumn > ghostColumn)
		pathDistance += (ghostDestinationColumn - ghostColumn);
	else if (ghostDestinationColumn < ghostColumn)
		pathDistance += (ghostColumn - ghostDestinationColumn);
	
	if(pathDistance == 0)
		pathDistance++;
}
