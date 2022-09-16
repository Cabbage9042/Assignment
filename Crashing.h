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
	KeyStatus escKey;
	KeyStatus wKey;
	KeyStatus aKey;
	KeyStatus sKey;
	KeyStatus dKey;
	FlyingObject *planet=NULL;
	FlyingObject *spaceship=NULL;
	

	//vector for collision
	D3DXVECTOR2 vectorBetweenPoints;

	
	D3DXVECTOR2 projectionOn(D3DXVECTOR2* projectedAxis, D3DXVECTOR2* projectionOfVector);
	void planetMoving();
	void stayInsideWindow(FlyingObject *obj);
	bool circlesCollided(Texture *circleA, Texture* circleB, D3DXVECTOR2* vectorBetweenPoints);
	
	//audio
	enum {crash};

	//D3DXVECTOR2 calculateFinalVelocity(D3DXVECTOR2 v1, D3DXVECTOR2 v2, float m1, float m2, D3DXVECTOR2 c1, D3DXVECTOR2 c2);

	float distanceSqBetweenCircle;

};

