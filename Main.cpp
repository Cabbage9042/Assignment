#pragma once
#include "Shell.h"
#include "FrameTimer.h"

#define CurrentLevel() shell.levelVector->back()

Shell shell = Shell();
FrameTimer timer = FrameTimer();

void Render() {

}

void main() {

	shell.InitializeGame();
	timer.Init(gameFPS);
	while (shell.windowManager.MyWindowIsRunning()) {
		CurrentLevel()->GetInput();
		CurrentLevel()->Update(timer.FramesToUpdate());
		CurrentLevel()->Render();
	}
	shell.UninitializeGame();

}