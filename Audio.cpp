#include "Audio.h"
#include <iostream>


void Audio::play(){
		Shell::audioManager.playSound(sound, &channel);

}



void Audio::stop() {
	channel->stop();
}

void Audio::Release()
{
	sound->release();
	sound = NULL;
	channel = NULL;
}

void Audio::setLoop(bool loopMode){
	if (loopMode == true) {
		sound->setMode(FMOD_LOOP_NORMAL);
	}
	else {
		sound->setMode(FMOD_LOOP_OFF);
	}
}

Audio::Audio(LPCSTR filepath, int createType) {
	if (createType == AUDIO_CREATE_SOUND){
		Shell::audioManager.createSound(filepath, &sound);
	}
	else {
		Shell::audioManager.createStream(filepath, &sound);
	}
}


