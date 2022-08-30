#pragma once

#include "GameManager.h"

//textures
enum { buttonStart,buttonQuit };

class MainMenu : public Game {

	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus leftButton;

	// Inherited via Game
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
};

