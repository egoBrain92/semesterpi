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
	int soundIndex;
	std::string soundPath;
} soundPair;

class AudioPlayer {
	public:
		AudioPlayer(soundPair*);
		void playSound(void);
		int chooseSoundindex(double[], int);
		std::string AudioPlayer::chooseSoundPath(void);
		void setPause(int);
		int getPause(void);
	
	private:
		int pause;
		soundPair* sound;
};

#endif
