#include <string>
#include <SFML/Audio.hpp>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

///Is used when no sound should be played.
#define NO_SOUND "NOSOUND"
///Path of the soundfile for the sensor that will measure in an 33° angle upwards.
#define SOUND_UPPER "SOUND_UPPER.wav"
///Path of the soundfile for the sensor that will measure directly in front of the user.
#define SOUND_MID "SOUND_MID.wav"
///Path of the soundfile for the sensor that will measure in an 33° angle downwards.
#define SOUND_LOWER "SOUND_LOWER.wav"
///Path of the soundfile for possible errors.
#define ERROR_SOUND "ERROR_SOUND.wav"

///The distance in which the sensor should trigger sound outputs.
#define MAX_DISTANCE 150

///Holds the soundIndex and the soundPath.
typedef struct soundPair {
	///Used to deterime which sound should be played.
	int soundIndex = -1;
	///Used to deterime which sound should be played.
	std::string soundPath = NO_SOUND;
} soundPair;

///Will play, load and choose the sounds in the appropriate moment.
class AudioPlayer {
	public:
		AudioPlayer();
		~AudioPlayer();
		void playSound();
		int chooseSoundindex(double[], int);
		std::string chooseSoundPath(void);
		void setPause(int);
		int getPause(void);
		soundPair* getSoundPair(void);
	
	private:
		int pause;
		
		soundPair* sound;
		
		sf::Sound player;
		sf::SoundBuffer sb1;
		sf::SoundBuffer sb2;
		sf::SoundBuffer sb3;
};

#endif
