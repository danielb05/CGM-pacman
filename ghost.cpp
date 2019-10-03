//#include "stdafx.h"

#include "ghost.h"


#include "ghost.h"
#include <iostream>
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
			//std::cout << "Width: " << displayWidth << " Height: " << displayHeight << "\n";
		}
		else if (elapsedTime >= remainingTime) {

			displayHeight += velocityRow * remainingTime;
			displayWidth += velocityColumn * remainingTime;
			ghostRow = ghostDestinationRow;
			ghostColumn = ghostDestinationColumn;
			isMoving = false;
			//std::cout << "Width: " << displayWidth << " Height: " << displayHeight << "\n";
		}
}

void Ghost::setVectorPoints() {

	displayHeight = ghostRow * 20;
	displayWidth = ghostColumn * 20;

	destinationHeight = ghostDestinationRow * 20;
	destinationWidth = ghostDestinationColumn * 20;

	if (ghostDestinationRow > ghostRow)
		pathDistance = (ghostDestinationRow - ghostRow);
	else
		pathDistance = (ghostRow - ghostDestinationRow);

	if (ghostDestinationColumn > ghostColumn)
		pathDistance += (ghostDestinationColumn - ghostColumn);
	else
		pathDistance += (ghostColumn - ghostDestinationColumn);

	//std::cout << "Distance: " << pathDistance << "\n";
}