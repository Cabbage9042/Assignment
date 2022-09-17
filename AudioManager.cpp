#include "AudioManager.h"
#include <iostream>

//FMOD::System AudioManager::* system = NULL;
//FMOD_RESULT AudioManager::result;
//void* AudioManager::extraDriverData = NULL;

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
	
}

void AudioManager::UninitializeAudio()
{
	system->release();
	system = NULL;
}

void AudioManager::createSound(LPCSTR filepath, FMOD::Sound** sound) {
	result = system->createSound(filepath, FMOD_DEFAULT, 0, sound);
}

void AudioManager::createStream(LPCSTR filepath, FMOD::Sound** sound)
{
	result = system->createStream(filepath, FMOD_DEFAULT, 0, sound);
}


void AudioManager::playSound(FMOD::Sound* sound, FMOD::Channel** channel)
{
	result = system->playSound(sound, 0, false, channel);
}


void AudioManager::updateSound()
{
	result = system->update();
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
