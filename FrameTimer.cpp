#include "FrameTimer.h"

void FrameTimer::Init(int fps)
{
	QueryPerformanceFrequency(&timerFreq);//Ask CPU how many ticks per second
	QueryPerformanceCounter(&timeNow); //Since the PC is switched on, how many ticks?
	QueryPerformanceCounter(&timePrevious);

	//init fps time info
	requested_FPS = fps;

	//The number of intervals in the given
	//timer, per frame at the requested rate.
	intervalsPerFrame = ((float)timerFreq.QuadPart / requested_FPS);
}

int FrameTimer::FramesToUpdate()
{
	int framesToUpdate = 0;
	QueryPerformanceCounter(&timeNow);

	//getting the delta time
	intervalsSinceLastUpdate = (float)timeNow.QuadPart - (float)timePrevious.QuadPart;
	framesToUpdate = (int)(intervalsSinceLastUpdate / intervalsPerFrame);

	//If we are not updating any frames, keep the old previous timer count  
	if (framesToUpdate != 0)
	{
		QueryPerformanceCounter(&timePrevious);
	}

	return framesToUpdate;
}

int FrameTimer::GetFPS()
{
	return requested_FPS;
}
