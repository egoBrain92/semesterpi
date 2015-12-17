#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>


using namespace std;

AudioPlayer::AudioPlayer(int pause)
:pause(pause){}

void AudioPlayer::playSound(string soundPath){
	sleep(pause);
	string sound = string("omxplayer ")+ soundPath;
	system(sound.c_str());
}

int AudioPlayer::getPause(){
	return pause;
}

void AudioPlayer::setPause(int newPause){
	pause = newPause;
}

soundPair* AudioPlayer::chooseSound(double distances[]){
	int i;
	soundPair* sound = new soundPair;
	int distance = MAXDISTANCE;	
	for(i = 0; i < sizeof(distances)/sizeof(*distances); i++){
		if(distances[i] <= distance && distances[i] <= MAXDISTANCE){
			distance = distances[i];
			sound->soundIndex = i;
		}else{
			sound->soundIndex = -1;
		}
	}
	switch(sound->soundIndex){
		case -1:
			sound->soundPath = NO_SOUND;
			break;		
		case 0:
			sound->soundPath = SOUND_UPPER;
			break;
		case 1:
			sound->soundPath = SOUND_MID;
			break;
		case 2:
			sound->soundPath = SOUND_LOWER;
			break;
		default: 
			sound->soundPath = ERROR_SOUND;
			sound->soundIndex = -2;
			break;
	}
	return sound;
}

double AudioPlayer::calcIntensity(double distance, int maxRange){
	double intensity;
	intensity = distance/maxRange;
	return intensity;
}



