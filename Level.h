#pragma once

#include "Map.h"
#include "Character.h"

#include "GameManager.h"
#include "GameOver.h"
#include "Victory.h"
#include "Pause.h"


class Level : public Game {
public:
	Map map;
	Character character;


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
	KeyStatus downKey;
	KeyStatus wKey;
	KeyStatus aKey;
	KeyStatus sKey;
	KeyStatus dKey;

	bool startBGM = true;
	bool isPlayingWalkingSound = false;

	void updateCharacterAnimation();
	void updateCharacterCollidedToWall();
	void updateTrapStatus();
	void characterMovingStatus();
	void enterTrapChecking();

	float calculatePan();
	
	int collidedXAxis;
	int collidedYAxis;
	int leverForWhichTrap;
	int collidedTrap;
	bool isEnteredTrap;

	//audio
	enum LevelAudio { bgm, lever, walking,scream };
};


