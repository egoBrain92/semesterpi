#include <string>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "NOSOUND"
#define SOUND_UPPER "HighkurzerTon.wav"
#define SOUND_MID "MidkurzerTon.wav"
#define SOUND_LOWER "LowKurzerTon.wav"
#define ERROR_SOUND "ErrorkurzerTon.wav"

#define MAXDISTANCE 150

typedef struct soundPair {
	int soundIndex = -1;
	std::string soundPath;
} soundPair;

class AudioPlayer {
	public:
		AudioPlayer(int, soundPair*);
		void playSound(std::string);
		soundPair* chooseSound(double[], int);
		void calcIntensity(double, int);
		void setPause(int);
		int getPause(void);
		soundPair* getSoundPair(void);


	
	private:
		int pause;
		soundPair* sound;
};

#endif
