#pragma once
#include "fmod.hpp"

class AudioManager{
public:
	FMOD::System* system;
	FMOD::Sound* sound;
	FMOD::Channel* channel = 0;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void playSound();
	void loadSounds();
	void updateSound();

	AudioManager();
	~AudioManager();
};

