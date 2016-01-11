#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

AudioPlayer::AudioPlayer(){
	this->pause = 1;
	
	try{
		sound = new soundPair();
	}catch(bad_alloc&){
		cout<<"failed to create soundPair the system will reboot now."<<endl;
		system("sudo reboot");
	}
	
	if (!sb1.loadFromFile(SOUND_UPPER)){
		cout<<"failed to load SOUND_MID the system will reboot now."<<endl;
		system("sudo reboot");
	}
	if (!sb2.loadFromFile(SOUND_LOWER)){
		cout<<"failed to load SOUND_MID the system will reboot now."<<endl;
		system("sudo reboot");
	}
	if (!sb3.loadFromFile(SOUND_MID)){
		cout<<"failed to load SOUND_MID the system will reboot now."<<endl;
		system("sudo reboot");
	}
}

AudioPlayer::~AudioPlayer(){
	delete sound;
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
		player.setBuffer(sb1);
		player.play();
	}

	if(this->sound->soundPath == SOUND_LOWER){
		player.setBuffer(sb2);
		player.play();
	}

	if(this->sound->soundPath == SOUND_MID){
		player.setBuffer(sb3);
		player.play();
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

soundPair* AudioPlayer::getSoundPair(){
	return this->sound;
}




