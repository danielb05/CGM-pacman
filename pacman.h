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

class Pacman {

public:
	int pacmanRow;
	int pacmanColumn;

public:
	
	Pacman(int pacmanRow, int pacmanColumn);
	void walk();
};

