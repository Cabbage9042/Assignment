#pragma once
#include "Shell.h"
#include "FrameTimer.h"
#include "GameManager.h"

#define CurrentLevel() GameManager::levelVector->back()

Shell shell = Shell();
GameManager gameManager = GameManager();
FrameTimer timer = FrameTimer();

void Render() {

}

void main() {

	gameManager.InitializeGame();
	timer.Init(gameFPS);
	while (Shell::windowManager.MyWindowIsRunning()) {
		CurrentLevel()->GetInput();
		CurrentLevel()->Update(timer.FramesToUpdate());
		CurrentLevel()->Render();
	}
	gameManager.UninitializeGame();

}