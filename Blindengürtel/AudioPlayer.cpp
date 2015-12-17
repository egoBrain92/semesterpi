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

pair chooseSound(double distances[]){
	int i;
	pair<string, int> sound;
	int soundNr = -1;
	int distance = MAXDISTANCE;	
	for(i = 0; i < sizeof(distances)/sizeof(*distances); i++){
		if(distances[i] <= distance){
			distance = distances[i];
			soundNr = i;

		}
	}
	switch(soundNr){
		case -1:
			sound.first_type = NO_SOUND;
			break;		
		case 0:
			sound = SOUND_UPPER;
			break;
		case 1:
			sound = SOUND_MID;
			break;
		case 2:
			sound = SOUND_LOWER;
			break;
		default: 
			sound = ERROR_SOUND;
			break;
	}
	return sound;
}

double AudioPlayer::calcIntensity(double distance, int maxRange){
	double intensity;
	intensity = distance/maxRange;
	return intensity;
}



