#pragma once

#include "Map.h"
#include "Character.h"

#include "GameManager.h"
enum { character };
enum {
	walkingUp, walkingDown, walkingLeft, walkingRight
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
	Character character;



	// Inherited via Game
	virtual void InitializeLevel() override;
	virtual void GetInput() override;
	virtual void Update(int framesToUpdate) override;
	virtual void Render() override;
	virtual void UninitializeLevel() override;
private:
	bool rectIsEqual(RECT a, RECT b);
};


