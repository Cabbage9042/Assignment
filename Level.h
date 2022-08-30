#pragma once
#include "Game.h"
#include "Map.h"
#include "Character.h"

#include "GameManager.h"
enum { character };
enum {
	walkingUp, walkingDown, walkingLeft, walkingRight
};
struct KeyStatus {
	bool isPressed = false, isHolding = false, isReleased = true;
};


class Level : public Game {
public:
	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus escKey;
	KeyStatus downKey;
	KeyStatus wKey;
	KeyStatus aKey;
	KeyStatus sKey;
	KeyStatus dKey;
	Map map;
	RectCollidedStatus characterCollidedStatus;


	bool characterIsMoving = false;
	int characterAnimationCounter;
	const int characterFPS = 10;

	// Inherited via Game
	virtual void InitializeLevel() override;
	virtual void GetInput() override;
	virtual void Update(int framesToUpdate) override;
	virtual void Render() override;
	virtual void UninitializeLevel() override;
private:
	void updateKeyStatus(bool keyDown, KeyStatus* key);
	bool rectIsEqual(RECT a, RECT b);
};


