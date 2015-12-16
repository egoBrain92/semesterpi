#include <string>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "......"
#define SOUND_UPPER "pfad/zur/sounddatei"
#define SOUND_MID "pfad/zur/sounddatei"
#define SOUND_LOWER "pfad/zur/sounddatei"
#define ERROR_SOUND "pfad/zur/sounddatei"

#define MAXDISTANCE 150


class AudioPlayer {
	public:
		AudioPlayer(int);
		void playSound();
		std::string chooseSound(int[]);
		int chooseIntensity(int);
		void setPause(int);
		int getPause();
	
	private:
		int pause;
};

#endif
