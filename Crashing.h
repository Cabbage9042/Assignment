#pragma once
#include "Game.h"
#include "GameManager.h"
#include "FlyingObject.h"

#define rotationSpeed 0.1


class Crashing : public Game{

public:


	// Inherited via Game
	virtual void InitializeLevel() override;
	virtual void GetInput() override;
	virtual void Update(int framesToUpdate) override;
	virtual void Render() override;
	virtual void UninitializeLevel() override;

private:

	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus downKey;
	KeyStatus wKey;
	KeyStatus aKey;
	KeyStatus sKey;
	KeyStatus dKey;
	FlyingObject *planet=NULL;
	FlyingObject *spaceship=NULL;

	void planetMoving();
	void stayInsideWindow(FlyingObject *obj);
	bool circlesCollided(Texture *circleA, Texture* circleB);

};

