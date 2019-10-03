#pragma once


#include <cmath>
#include <cstdlib>

class NextDirection {

public:
	// Positions: 0 = North, 1 = South, 2 = West, 3 = East
	bool visitedDirection[4];
	int randomize();
	void startVisiting();
};