#pragma once

#include "GameManager.h" //must include
#include "Character.h"
//textures
enum { buttonStart, buttonQuit };

//sprite
enum { pointer, character };

//platform
enum { ground, buttonStartTop, buttonQuitTop};
class MainMenu : public Game {

	//must
	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus leftButton;
	Character character;
	KeyStatus spaceKey;
	

	// Inherited via Game, must
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
	
	void pointerStayInsideWindow();
	void pointerOnButton();
	void updateCollidedToButton();
};

