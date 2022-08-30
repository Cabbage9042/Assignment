#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

class Cell{
public:
	int nthColumn;
	int nthRow;
	char type;
	RECT positionRect;
	Cell(int nthColumn,	int nthRow, char type, RECT positionRect) {
		this->nthColumn = nthColumn;
		this->nthRow = nthRow;
		this->type = type;
		this->positionRect = positionRect;
	}
};

