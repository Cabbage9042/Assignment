#pragma once

#include "GameManager.h" //must include
#include "Character.h"
#include "Panel.h"

//textures
enum { buttonStart, buttonQuit };

//sprite
enum { pointer, character };

//platform
enum { ground, buttonStartTop, buttonQuitTop};

enum optionPanelLabel{ bgmLabel, soundEffectLabel};

enum optionPanelSlider{ bgmSlider};

class MainMenu : public Game {

	//must
	KeyStatus altKey;
	KeyStatus f4Key;
	KeyStatus leftButton;
	Character character;
	KeyStatus spaceKey;
	KeyStatus aKey;
	KeyStatus dKey;
	bool startBGM = true;

	Panel* buttonPanel;
	Panel* optionPanel;

	// Inherited via Game, must
	void InitializeLevel() override;
	void GetInput() override;
	void Update(int framesToUpdate) override;
	void Render() override;
	void UninitializeLevel() override;
	
	void pointerStayInsideWindow();
	bool buttonIsClicked();
	void updateCollidedToButton();
	void resetToDefault(bool resetBGM = true);

//audio
	enum audio { button, bgm };
};

