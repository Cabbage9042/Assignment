#pragma once

#include "GameManager.h" //must include

//textures
enum { PContinue,PRestart, PReturnmm };

class Pause : public Game {

	//must
	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus leftButton;

	//audio
	enum { button };

	// Inherited via Game, must
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
};
