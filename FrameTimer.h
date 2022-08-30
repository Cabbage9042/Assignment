#pragma once
#include<Windows.h>

class FrameTimer
{
public:
	void Init(int);
	int FramesToUpdate();
	int GetFPS();
private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;
	int requested_FPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;

};

