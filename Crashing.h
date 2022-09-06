#pragma once
#include "Game.h"
#include "GameManager.h"
#include "FlyingObject.h"

class Crashing : public Game{

public:

	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus downKey;
	FlyingObject *planet=NULL;
	FlyingObject *spaceship=NULL;

	// Inherited via Game
	virtual void InitializeLevel() override;
	virtual void GetInput() override;
	virtual void Update(int framesToUpdate) override;
	virtual void Render() override;
	virtual void UninitializeLevel() override;
};

