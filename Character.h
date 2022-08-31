#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

enum { walkingUp, walkingDown, walkingLeft, walkingRight };

struct RectCollidedStatus {
	RECT topCollided = RECT();
	RECT leftCollided = RECT();
	RECT bottomCollided = RECT();
	RECT rightCollided = RECT();
};

class Character{

#define DEFAULT_VELOCITY D3DXVECTOR2(0,0)
#define DEFAULT_SPEED 5
public:

	D3DXVECTOR2 velocity = DEFAULT_VELOCITY;
	Sprite sprite;
	RectCollidedStatus characterCollidedStatus;
	bool characterIsMoving = false;
	int characterAnimationCounter = 0;
	const int characterFPS = 10;

};

