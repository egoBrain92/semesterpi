#include "AudioPlayer.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

///Loads the soundfiles and creates a soundPair. Also sets pause to 1 for the first measurement.
AudioPlayer::AudioPlayer(){
	this->pause = 1;
	
	try{
		sound = new soundPair();
	}catch(bad_alloc&){
		writeToLogAudioPlayer("Failed to create soundPair the system will reboot now.");
		//system("sudo reboot");
	}
	
	if (!sb1.loadFromFile(SOUND_UPPER)){
		writeToLogAudioPlayer("Failed to create SOUND_UPPER the system will reboot now.");
		//system("sudo reboot");
	}
	if (!sb2.loadFromFile(SOUND_LOWER)){
		writeToLogAudioPlayer("Failed to create SOUND_LOWER the system will reboot now.");
		//system("sudo reboot");
	}
	if (!sb3.loadFromFile(SOUND_MID)){
		writeToLogAudioPlayer("Failed to create SOUND_MID the system will reboot now.");
		//system("sudo reboot");
	}
}

///Destroys the created AudioPlayer object and uses delete to free the memeory of the variable sound.
AudioPlayer::~AudioPlayer(){
	delete sound;
}

///Chooses the soundIndex for the latest measurements.
///@param distances[] is the array with the latest averaged measurement.
///@param amountSen the number of sensor which take measurements.
///@return returns the soundIndex which should be played.
int AudioPlayer::chooseSoundindex(double distances[], int amountSen){
	int i;
	int distance;

	this->sound->soundIndex = -1;
	distance = MAX_DISTANCE;

	for(i = 0; i < amountSen; i++){
		if(distances[i] <= distance && distances[i] > 0){
			distance = distances[i];
			this->sound->soundIndex = i;
		}
	}
	return this->sound->soundIndex;
}

///Palys the sound that is specified in soundPath.\n
///player.play() creates a new thread and therefore the audio will play without blocking anything in the process.
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

///Chooses the soundPath that should be played for the latest measurement.
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

///Getter for pause.
///@return Returns the duration of the silence in between two sound outputs.
int AudioPlayer::getPause(){
	return this->pause;
}

///Sets the duration of the silence in between two sound outputs.
///@param newPause Will be the new duration of the silence in between two sound outputs.
void AudioPlayer::setPause(int newPause){
	this->pause = newPause;
}

///Getter for sound.
///@return Returns the soundPair which includes the soundPath and soundIndex.
soundPair* AudioPlayer::getSoundPair(){
	return this->sound;
}

///Logs error messages to the log.txt file in the project directory.
void AudioPlayer::writeToLogAudioPlayer(const string message){
	
	FILE* file = fopen("log.txt", "a");
	if(file != NULL){
		fprintf(file, "%s\n", message.c_str());
		fclose(file);
	}
}



