#pragma once

#include "GameManager.h" //must include
#include "Character.h"
#include "Panel.h"
#include <sstream>

//textures
enum { buttonStart, buttonQuit };

//sprite
enum { pointer, character };

//platform
enum { ground, buttonStartTop, buttonQuitTop};

enum optionPanelLabel{ bgmLabelEnum, bgmVolumeLabelEnum, effectLabelEnum, effectVolumeLabelEnum};

enum optionPanelSlider{ bgmSlider, effectSlider};

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
	
	Text* bgmVolumeLabel,* effectVolumeLabel;
	char bgmVolumeLabelString[4] = "100", effectVolumeLabelString[4] = "100";

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
	void moveCharacter();

//audio
	enum audio { button, bgm };
};

