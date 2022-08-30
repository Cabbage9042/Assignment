#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Lever{
public:
	int nthColumn;
	int nthRow;
	RECT positionRect;
	bool hasTurnedOn;
	Lever(int nthColumn, int nthRow, RECT positionRect,bool hasTurnedOn) {
		this->nthColumn = nthColumn;
		this->nthRow = nthRow;
		this->positionRect = positionRect;
		this->hasTurnedOn = hasTurnedOn;
	}
	Lever() {
		nthColumn = 0;
		nthRow = 0;
		positionRect = RECT();
		hasTurnedOn = false;
	}
};

