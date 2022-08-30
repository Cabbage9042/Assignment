#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Cell{
public:
	char type;
	RECT positionRect;
	Cell(char type, RECT positionRect) {
		this->type = type;
		this->positionRect = positionRect;
	}
};

