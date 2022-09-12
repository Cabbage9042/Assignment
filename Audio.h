#pragma once
#include "Shell.h"

class Audio{
public:
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;

	void play();
	void stop();
	void Release();
	void setLoop(bool loopMode);

	Audio(LPCSTR filepath);
};

