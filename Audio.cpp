#include "Audio.h"
#include <iostream>


void Audio::play(){
	if (channel == NULL) {
		Shell::audioManager.playSound(sound, &channel);
	}
	else {
		channel->setPaused(false);
	}
}

void Audio::pause(){
	channel->setPaused(true);
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

Audio::Audio(LPCSTR filepath){
	Shell::audioManager.createSound(filepath, &sound);
}


