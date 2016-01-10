#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <SFML/Audio.hpp>



using namespace std;

AudioPlayer::AudioPlayer(soundPair* sp)
:sound(sp){
	sound->soundIndex= -1;
	sound->soundPath = NO_SOUND;
	this->pause = 1;
}

int AudioPlayer::chooseSoundindex(double distances[], int amountSen){
	int i;
	int distance;

	this->sound->soundIndex = -1;
	distance = MAXDISTANCE;

	for(i = 0; i < amountSen; i++){
		if(distances[i] <= distance){
			distance = distances[i];
			this->sound->soundIndex = i;
		}
	}
	return this->sound->soundIndex;
}

void AudioPlayer::playSound(){
	if(this->sound->soundPath == SOUND_UPPER){
		sound.setBuffer(sb1);
		sound.play();
	}

	if(this->sound->soundPath == SOUND_LOWER){
		sound.setBuffer(sb2);
		sound.play();
	}

	if(this->sound->soundPath == SOUND_MID){
		sound.setBuffer(sb3);
		sound.play();
	}
}

int AudioPlayer::getPause(){
	return this->pause;
}

void AudioPlayer::setPause(int newPause){
	this->pause = newPause;
}

string AudioPlayer::chooseSoundPath(){
	switch(this->sound->soundIndex){
			case -1:
				this->sound->soundPath = NO_SOUND;
				break;
			case 0:
				this->sound->soundPath = SOUND_UPPER;
				break;
			case 1:
				this->sound->soundPath = SOUND_MID;
				break;
			case 2:
				this->sound->soundPath = SOUND_LOWER;
				break;
			default:
				this->sound->soundPath = ERROR_SOUND;
				break;
		}
	return this->sound->soundPath;
}




