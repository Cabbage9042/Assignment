#pragma once
#include "Game.h"

//textures
enum { buttonStart,buttonQuit };

class MainMenu : public Game {

	bool altKeyPressed = false;
	bool f4KeyPressed = false;
	bool escKeyPressed = false;

	// Inherited via Game
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
};

