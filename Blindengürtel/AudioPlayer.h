#include <string>
#include <SFML/Audio.hpp>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

///Is used when no sound should be played.
#define NO_SOUND "NOSOUND"
///Path of the soundfile for the sensor that will measure in an 33° angle upwards.
#define SOUND_UPPER "/home/pi/Desktop/autostartfiles/Blindengürtel/SOUND_UPPER.wav"
///Path of the soundfile for the sensor that will measure directly in front of the user.
#define SOUND_MID "/home/pi/Desktop/autostartfiles/Blindengürtel/SOUND_MID.wav"
///Path of the soundfile for the sensor that will measure in an 33° angle downwards.
#define SOUND_LOWER "/home/pi/Desktop/autostartfiles/Blindengürtel/SOUND_LOWER.wav"
///Path of the soundfile for possible errors.
#define ERROR_SOUND "/home/pi/Desktop/autostartfiles/Blindengürtel/ERROR_SOUND.wav"

///The distance in which the sensor should trigger sound outputs.
#define MAX_DISTANCE 150

///Holds the soundIndex and the soundPath.
typedef struct soundPair {
	public:
		///Used to deterime which sound should be played.
		int soundIndex = -1;
		///Used to deterime which sound should be played.
		std::string soundPath = NO_SOUND;
} soundPair;

///Will play, load and choose the sounds in the appropriate moment.
class AudioPlayer {
	public:
		///Loads the soundfiles and creates a soundPair. Also sets pause to 1 for the first measurement.
		AudioPlayer();
		///Destroys the created AudioPlayer object and uses delete to free the memeory of the variable sound.
		~AudioPlayer();
		
		///Palys the sound that is specified in soundPath.\n
		///player.play() creates a new thread and therefore the audio will play without blocking anything in the process.
		void playSound();
		
		///Chooses the soundIndex for the latest measurements.
		///@param distances[] is the array with the latest averaged measurement.
		///@param amountSen the number of sensor which take measurements.
		///@return returns the soundIndex which should be played.
		int chooseSoundindex(double distances[], int amountSen);
		
		///Chooses the soundPath that should be played for the latest measurement.
		///@returns returns the soundPath to the file which should be played
		std::string chooseSoundPath(void);
		
		///Sets the duration of the silence in between two sound outputs.
		///@param newPause Will be the new duration of the silence in between two sound outputs.
		void setPause(int);
		
		///Getter for pause.
		///@return Returns the duration of the silence in between two sound outputs.
		int getPause(void);
		
		///Getter for sound.
		///@return Returns the soundPair which includes the soundPath and soundIndex.
		soundPair* getSoundPair(void);

	
	private:
		
		///Stores the duration of the silence in between two sound outputs.
		int pause;
		
		///Stores a soundPair that will hold the soundIndex and soundPath.This is needed for playing the correct sound.
		soundPair* sound;
		
		///The player will actually play the sounds by creating a new thread in the background.
		sf::Sound player;
		///Stores the soundfile defined by SOUND_UPPER.
		sf::SoundBuffer sb1;
		///Stores the soundfile defined by SOUND_LOWER.
		sf::SoundBuffer sb2;
		///Stores the soundfile defined by SOUND_MID.
		sf::SoundBuffer sb3;
};

#endif
