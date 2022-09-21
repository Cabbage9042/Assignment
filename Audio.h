#pragma once
#include "Shell.h"

enum createMode {
	AUDIO_CREATE_SOUND,
	AUDIO_CREATE_STREAM
};

enum channelGroupEnum {
	bgmGroup,
	effectGroup
};

class Audio{
public:
	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;
	FMOD::ChannelGroup** channelGroup = NULL;

	void play();
	void stop();
	void Release();
	void setLoop(bool loopMode);

	Audio(LPCSTR filepath,int channelGroup, int createType = AUDIO_CREATE_SOUND);
};

