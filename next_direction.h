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

class NextDirection {

	public:
		// Positions: 0 = North, 1 = South, 2 = West, 3 = East
		bool visitedDirection[4];
		int randomize();
		void startVisiting();
};