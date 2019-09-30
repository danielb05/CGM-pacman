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
#include "map.h"

class Pacman {

	public:
		// Positions: 0 = North, 1 = South, 2 = West, 3 = East
		int pacmanPosition[2];
		void born(Map map);
		void walk();
};