#pragma once
#include "fmod.hpp"
#include <d3d9.h>

//documentation file:///C:/Program%20Files%20(x86)/FMOD%20SoundSystem/FMOD%20Studio%20API%20Windows/doc/FMOD%20API%20User%20Manual/welcome.html
class AudioManager{
public:
	FMOD::System* system;
	FMOD_RESULT result;
	void* extraDriverData = 0;

	void InitializeAudio();
	void UninitializeAudio();
	void createSound(LPCSTR filepath, FMOD::Sound** sound);
	void playSound(FMOD::Sound* sound, FMOD::Channel** channel);
	void updateSound();

	AudioManager();
	~AudioManager();
};

