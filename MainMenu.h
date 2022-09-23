#pragma once

#include "GameManager.h" //must include
#include "Character.h"
#include "Panel.h"
#include <sstream>
#define panelVelocity D3DXVECTOR2(60,0)

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
	bool startBGM = true;

	Panel* buttonPanel;
	Panel* optionPanel;
	Button* optionButton;
	enum{left = -1,right=1};
	int panelIsMovingTo = 0;
	bool panelIsMoving = false;

	
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
	void volumeToString(char string[], int volume);

//audio
	enum audio { button, bgm };
};

