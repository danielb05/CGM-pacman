//#include "stdafx.h"
#include "ghost.h"
#include <iostream>
Ghost::Ghost(){
	ghostRow = 0;
	ghostColumn = 0;
	ghostDestinationRow = 0;
	ghostDestinationColumn = 0;
	isMoving = false;
	displayWidth = 0.0;
	displayHeight = 0.0;
	destinationWidth = 0.0;
	destinationHeight = 0.0;
	velocityRow = 0.0;
	velocityColumn = 0.0;
	remainingTime = 0.0;
}

void Ghost::setPosition(int ghostRow, int ghostColumn){
	this->ghostRow = ghostRow;
	this->ghostColumn = ghostColumn;
}

void Ghost::startWalk(){

	setVectorPoints();

	velocityColumn = (destinationWidth - displayWidth) / GHOST_VELOCITY;
	velocityRow = (destinationHeight - displayHeight) / GHOST_VELOCITY;

	isMoving = true;
	remainingTime = GHOST_VELOCITY;
}

void Ghost::refreshWalk(long elapsedTime){

	if(isMoving)
		if(elapsedTime < remainingTime){
		
			displayHeight += velocityRow * elapsedTime;
			displayWidth += velocityColumn * elapsedTime;
			remainingTime -= elapsedTime;
std::cout << "Width: " << displayWidth << " Height: " << displayHeight << "\n";
		} else if(elapsedTime >= remainingTime) {
		
			displayHeight += velocityRow * remainingTime;
			displayWidth += velocityColumn * remainingTime;
			isMoving = false;
std::cout << "Width: " << displayWidth << " Height: " << displayHeight << "\n";
		}
}

void Ghost::setVectorPoints(){
	
	displayHeight = ghostRow * 20;
	displayWidth = ghostColumn * 20;

	destinationHeight = ghostDestinationRow * 20;
	destinationWidth = ghostDestinationColumn * 20;
}