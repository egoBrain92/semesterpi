#include <string>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "/home/pi/Desktop/woop.mp3"
#define SOUND_UPPER "/home/pi/Desktop/woop.mp3"
#define SOUND_MID "/home/pi/Desktop/woop.mp3"
#define SOUND_LOWER "/home/pi/Desktop/woop.mp3"
#define ERROR_SOUND "/home/pi/Desktop/woop.mp3"

#define MAXDISTANCE 150

typedef struct soundPair {
	int soundIndex = -1;
	std::string soundPath;
} soundPair;

class AudioPlayer {
	public:
		AudioPlayer(int, soundPair*);
		void playSound(std::string);
		soundPair* chooseSound(double[]);
		double calcIntensity(double, int);
		void setPause(int);
		int getPause(void);
		soundPair* getSoundPair(void);


	
	private:
		int pause;
		soundPair* sound;
};

#endif
