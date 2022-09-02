#pragma once

#include "GameManager.h" //must include

//textures
enum { buttonStart,buttonQuit };

class MainMenu : public Game {

	//must
	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus leftButton;

	// Inherited via Game, must
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
};

