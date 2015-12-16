#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

AudioPlayer::AudioPlayer(int pause)
:pause(pause){}

void playSound(string soundPath){
	sleep(getPause());
	string sound = string("omxplayer ")+ soundPath;
	system(sound.c_str());
}

int getPause(){
	return pause;
}

string chooseSound(int distances[]){
	int i;
	string sound;
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
			sound = NO_SOUND;
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



