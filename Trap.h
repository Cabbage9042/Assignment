#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Lever.h"

struct RelativePosition {
	int row = -1, col = -1;
};

class Trap {
public:

	RelativePosition trapTopRightPosition;
	bool isSet = false;
	Lever lever = Lever();

};

