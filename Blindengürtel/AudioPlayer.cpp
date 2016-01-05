#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>


using namespace std;

AudioPlayer::AudioPlayer(int pause, soundPair* sp)
:pause(pause), sound(sp){}

void AudioPlayer::playSound(string soundPath){
	sleep(pause);
	string sound = string("aplay ")+ soundPath;
	system(sound.c_str());
}

int AudioPlayer::getPause(){
	return this->pause;
}

soundPair* AudioPlayer::getSoundPair(){
	return this->sound;
}


void AudioPlayer::setPause(int newPause){
	this->pause = newPause;
}

soundPair* AudioPlayer::chooseSound(double distances[]){
	int i;
	int distance = MAXDISTANCE;	
	for(i = 0; i < sizeof(distances)/sizeof(*distances); i++){
		if(distances[i] <= distance && distances[i] <= MAXDISTANCE){
			distance = distances[i];
			this->sound->soundIndex = i;
		}else{
			this->sound->soundIndex = -1;
		}
	}
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
			this->sound->soundIndex = -2;
			break;
	}
	return this->sound;
}

double AudioPlayer::calcIntensity(double distance, int maxRange){
	double intensity;
	intensity = distance/maxRange;
	return intensity;
}



