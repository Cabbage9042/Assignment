#include "AudioManager.h"
#include <iostream>

//FMOD::System AudioManager::* system = NULL;
//FMOD_RESULT AudioManager::result;
//void* AudioManager::extraDriverData = NULL;

void AudioManager::InitializeAudio()
{
	result = FMOD::System_Create(&system);
	result = system->init(32, FMOD_INIT_NORMAL, extraDriverData);
	result = system->createChannelGroup("", &bgmChannelGroup);
	result = system->createChannelGroup("", &effectChannelGroup);
	
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


void AudioManager::playSound(FMOD::Sound* sound, FMOD::Channel** channel, FMOD::ChannelGroup *channelGroup)
{
	result = system->playSound(sound, channelGroup, false, channel);
}


void AudioManager::updateSound()
{
	result = system->update();
}

void AudioManager::setBgmVolume(float volume)
{
	bgmChannelGroup->setVolume(volume);
}

void AudioManager::setEffectVolume(float volume)
{
	effectChannelGroup->setVolume(volume);
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
