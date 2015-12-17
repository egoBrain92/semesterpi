#include <string>
#include <utility>

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#define NO_SOUND "/home/pi/Desktop/woop.mp3"
#define SOUND_UPPER "/home/pi/Desktop/woop.mp3"
#define SOUND_MID "/home/pi/Desktop/woop.mp3"
#define SOUND_LOWER "/home/pi/Desktop/woop.mp3"
#define ERROR_SOUND "/home/pi/Desktop/woop.mp3"

#define MAXDISTANCE 150


class AudioPlayer {
	public:
		AudioPlayer(int);
		void playSound(std::string);
		std::pair chooseSound(double[]);
		double calcIntensity(double, int);
		void setPause(int);
		int getPause(void);
	
	private:
		int pause;
};

#endif
