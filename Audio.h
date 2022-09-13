#pragma once
#include "Shell.h"

enum {
	AUDIO_CREATE_SOUND,
	AUDIO_CREATE_STREAM
};

class Audio{
public:
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;

	void play();
	void stop();
	void Release();
	void setLoop(bool loopMode);

	Audio(LPCSTR filepath, int createType = AUDIO_CREATE_SOUND);
};

