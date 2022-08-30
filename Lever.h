#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Lever{
public:
	int nthColumn;
	int nthRow;
	RECT positionRect;
	Lever(int nthColumn, int nthRow, RECT positionRect) {
		this->nthColumn = nthColumn;
		this->nthRow = nthRow;
		this->positionRect = positionRect;
	}
	Lever() {
		nthColumn = 0;
		nthRow = 0;
		positionRect = RECT();
	}
};

