#pragma once
#include "Sprite.h"

enum { walkingUp, walkingDown, walkingLeft, walkingRight };

struct RectCollidedStatus {
	RECT topCollided = RECT();
	RECT leftCollided = RECT();
	RECT bottomCollided = RECT();
	RECT rightCollided = RECT();
};

class Character{

#define DEFAULT_VELOCITY 5
public:

	int velocity = DEFAULT_VELOCITY;
	Sprite sprite;
	RectCollidedStatus characterCollidedStatus;
	bool characterIsMoving = false;
	int characterAnimationCounter = 0;
	const int characterFPS = 10;

};

