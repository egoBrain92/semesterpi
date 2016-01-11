#include "AudioPlayer.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

///loads the soundfiles and creates the soundPair also sets pause to 1 for the first few measurement
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

///chooses the soundIndex for the latest measurement
///@param distances[] is the array with the latest middeled measurement 
///@param amountSen the number of sensor which take measurements 
///@return returns the soundIndex which should be played
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

///palys the sound that is specified by soundPath
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

///chooses the soundPath that should be played for the latest measurement
///@returns returns the soundPath to the file which should be played
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

///@return returns the duration of the silence in between two sound outputs
int AudioPlayer::getPause(){
	return this->pause;
}

///set the duration of the silence in between two sound outputs
void AudioPlayer::setPause(int newPause){
	this->pause = newPause;
}

///@return returns the soundPair which includes the soundPath and soundIndex
soundPair* AudioPlayer::getSoundPair(){
	return this->sound;
}




