#include <string>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "......"
#define SOUND_UPPER "pfad/zur/sounddatei"
#define SOUND_MID "pfad/zur/sounddatei"
#define SOUND_LOWER "pfad/zur/sounddatei"
#define ERROR_SOUND "pfad/zur/sounddatei"

#define MAXDISTANCE 150

typedef struct soundPair {
	int soundIndex = -1;
	std::string soundPath;
} soundPair;

class AudioPlayer {
	public:
		AudioPlayer(int);
		void playSound(std::string);
		soundPair* chooseSound(double[]);
		double calcIntensity(double, int);
		void setPause(int);
		int getPause(void);
	
	private:
		int pause;
};

#endif
