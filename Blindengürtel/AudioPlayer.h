#include <string>
#include <SFML/Audio.hpp>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "NOSOUND"
#define SOUND_UPPER "SOUND_UPPER.wav"
#define SOUND_MID "SOUND_MID.wav"
#define SOUND_LOWER "SOUND_LOWER.wav"
#define ERROR_SOUND "ERROR_SOUND.wav"

#define MAXDISTANCE 150

typedef struct soundPair {
	int soundIndex = -1;
	std::string soundPath = NO_SOUND;
} soundPair;

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
