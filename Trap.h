#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Lever.h"

struct RelativePosition {
	int row = -1, col = -1;
};

class Trap {
public:
	RECT positionRect;
	RelativePosition trapBottomRightPosition;
	D3DXVECTOR2 positionBetweenWalls = D3DXVECTOR2();
	bool isSet = false;
	Lever lever = Lever();

};

