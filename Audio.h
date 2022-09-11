#pragma once
#include "Shell.h"

class Audio{
public:
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;

	void play();
	void pause();
	void stop();
	void Release();

	Audio(LPCSTR filepath);
};

