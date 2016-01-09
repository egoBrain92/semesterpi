#include <stdio.h>
#include <unistd.h>
#include <iostream>
//#include <pthread.h>
#include <cstdlib>
#include <wiringPi.h>
#include "SensorMid.h"
#include "SensorUp.h"
#include "SensorLow.h"
#include "AudioPlayer.h"
#include <thread>
#include <mutex>
#include <SFML/Audio.hpp>

#define NO_SOUND "NOSOUND"
#define SOUND_UPPER "sound3.wav"
#define SOUND_MID "sound4.wav"
#define SOUND_LOWER "LowKurzerTon.wav"
#define ERROR_SOUND "ErrorkurzerTon.wav"


#define NUMBER_OF_SENSORS 3
#define INIT_ARRAY_VAL 999999
#define ECHO_PIN_SUP	15
#define TRIG_PIN_SUP	16

#define ECHO_PIN_SLOW	1
#define TRIG_PIN_SLOW	4

#define ECHO_PIN_SMID	5
#define TRIG_PIN_SMID	6

using namespace std;



mutex mtx1;
mutex mtx2;
mutex mtx3;

		/*distances of all Sensors
		0 : Sensor Up
		1 : Sensor Mid
		2 : Sensor down
		*/
double distances[NUMBER_OF_SENSORS]= {INIT_ARRAY_VAL, INIT_ARRAY_VAL ,INIT_ARRAY_VAL};
double intensity;	
string soundPath;



void setup() {
        wiringPiSetup();
        pinMode(ECHO_PIN_SUP, INPUT);
        pinMode(TRIG_PIN_SUP, OUTPUT);
        
        digitalWrite(TRIG_PIN_SUP, LOW);

		pinMode(TRIG_PIN_SLOW, OUTPUT);
        pinMode(ECHO_PIN_SLOW, INPUT);
        digitalWrite(TRIG_PIN_SLOW, LOW);

		pinMode(ECHO_PIN_SMID, INPUT);
		pinMode(TRIG_PIN_SMID, OUTPUT);
        digitalWrite(TRIG_PIN_SMID, LOW);

        //delay(30);
}

//thread function: same function for different threads, just differs in parameter (polymorphy)
/*void threadbla(ISensor* mySen){
	

	while(1){
		
		
		
		//mtx2.lock();
		mySen->collectMeasurements();
		//mtx2.unlock();
		
		
		
		//mtx3.lock();
		usleep(50000);
		//mtx3.unlock();
		
		
		
		mtx1.lock();
		mySen->pushData(distances, mySen->getId(), mySen->calcMidValue());
		mtx1.unlock();
		
	}
}*/


void apFunction(AudioPlayer* ap){
	string sound;
	while(1){

		
		mtx1.lock();
		sound = ap->chooseSound(distances, NUMBER_OF_SENSORS)->soundPath;
		mtx1.unlock();
		
		
		//delayMicroseconds(1000);
		//cout<<"soundpath: "<<sound<<endl;
		if(sound != NO_SOUND){
			
			//cout<<"soundpath: "<<sound<<endl;
			mtx1.lock();
	
			ap->calcIntensity(distances[ap->getSoundPair()->soundIndex], MAXDISTANCE);
			
			mtx1.unlock();
			
			mtx1.lock();
			ap->playSound(ap->getSoundPair()->soundPath);
			mtx1.unlock();
			mtx1.lock();
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
		mtx1.unlock();
		//cout<<"la"<<endl;
			//delayMicroseconds(ap->getPause()*1000000);
			delayMicroseconds(500000);
			//cout<<"sound: "<<sound<<endl;
			
		}
		
	}
}
void myFunction(){
	sf::SoundBuffer sb1;
	sf::SoundBuffer sb2;
	sf::SoundBuffer sb3;
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound sound3;
	
	sb1.loadFromFile(SOUND_UPPER);
	sound1.setBuffer(sb1);
	
	sb2.loadFromFile(SOUND_LOWER);
	sound2.setBuffer(sb2);
	
	sb3.loadFromFile(SOUND_MID);
	sound3.setBuffer(sb3);
	
	while(1){
		if(soundPath == SOUND_UPPER){
			sound1.setBuffer(sb1);
			sound1.play();
		}
		
		if(soundPath == SOUND_LOWER){
			sound1.setBuffer(sb2);
			sound1.play();
			//sound2.play();
		}
		
		if(soundPath == SOUND_MID){
			sound1.setBuffer(sb3);
			sound1.play();
			//sound3.play();
		}

		usleep(intensity * 1000000);
	}
}


int main()
{
	setup();
	long travelTimeUp;
	long travelTimeLow;
	long travelTimeMid;
	
	int soundIndex;
	int i;
	int distance;
	
	bool checkMid;
	bool checkUp;
	bool checkLow;
	soundPair* sp = new soundPair;
	AudioPlayer* ap = new AudioPlayer(1, sp);
	//string sound;
	
	//thread t4;
	

	SensorMid* senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1);
	SensorUp* senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	SensorLow* senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);
	
	thread t4(myFunction);
	t4.detach();
	
	
	
	
	while(1){
		checkMid = false;
		checkUp = false;
		checkLow = false;
		
		senLow->initiateMeasurement();
		//usleep(500);
		senUp->initiateMeasurement();
		//usleep(500);
		senMid->initiateMeasurement();
		usleep(400);
		
	//	cout<<"bla"<<endl;
		while(digitalRead(senMid->getEchoPin()) == LOW && digitalRead(senUp->getEchoPin()) == LOW && digitalRead(senLow->getEchoPin()) == LOW){
			//cout<<"wait"<<endl;
			}
		long startTime = micros();
		//cout<<"startTime: "<<startTime<<endl;
		//usleep(10000);
		while(digitalRead(senMid->getEchoPin()) == HIGH || digitalRead(senUp->getEchoPin()) == HIGH || digitalRead(senLow->getEchoPin()) == HIGH){
		//cout<<"while"<<endl;
			if(digitalRead(senMid->getEchoPin()) == LOW && checkMid == false){
				//cout<<"senMid"<<endl;
				//cout<<"micros(): "<<micros()<<endl;
				travelTimeMid = micros() - startTime;
				
				checkMid = true;
			}
			if(digitalRead(senUp->getEchoPin()) == LOW && checkUp == false){
				//cout<<"senUp"<<endl;
				travelTimeUp = micros() - startTime;
				checkUp = true;
			}
			if(digitalRead(senLow->getEchoPin()) == LOW && checkLow == false){
				//cout<<"senLow"<<endl;
				travelTimeLow = micros() - startTime;
				checkLow = true;
			}		
		}
		cout<<"travelTimeUp: "<<travelTimeUp<<" / travelTimeMid: "<<travelTimeMid<<" / travelTimeLow: "<<travelTimeLow<<endl;
		senMid->collectMeasurements(travelTimeMid);
		senUp->collectMeasurements(travelTimeUp);
		senLow->collectMeasurements(travelTimeLow);
		
		senMid->pushData(distances, senMid->getId(), senMid->calcMidValue());
		senUp->pushData(distances, senUp->getId(), senUp->calcMidValue());
		senLow->pushData(distances, senLow->getId(), senLow->calcMidValue());
	
		
		usleep(50000);
		
	
	soundIndex = -1;
	distance = 150;

	for(i = 0; i < NUMBER_OF_SENSORS; i++){ //sizeof(distances/sizeof(&distances[0])
		//cout<<"distance["<<i<<"]"<<sizeof(distances)/sizeof(distances[0])<<endl;
		if(distances[i] <= distance){
			distance = distances[i];
			soundIndex = i;
		}
	}
	mtx1.lock();
	switch(soundIndex){
		case -1:
			soundPath = NO_SOUND;
			break;		
		case 0:
			soundPath = SOUND_UPPER;
			break;
		case 1:
			soundPath = SOUND_MID;
			break;
		case 2:
			soundPath = SOUND_LOWER;
			break;
		default: 
			soundPath = ERROR_SOUND;
			break;
	}
	mtx1.unlock();
	
	if(soundIndex != -1){
	mtx2.lock();
	intensity = distances[soundIndex]/MAXDISTANCE;
	mtx2.unlock();
	}		
			
			
	
		
		/*sound.setBuffer(sb);
		sound.play();*/
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	}
	
    /*
	int checkMid;
	int checkLow;
	int checkUp;
	int checkAP;
	*/
	//sleep(1);
	//initialize threads
	/*thread t1 (threadbla, senMid);
	thread t2 (threadbla, senLow);
	thread t3 (threadbla, senUp);
	thread t4 (apFunction, ap);
	*/
	/*sf::SoundBuffer buffer;
	sf::Sound sound;

		
	if (!buffer.loadFromFile("HighkurzerTon.wav")){
		cout<<"error"<<endl;
	}

	sound.setBuffer(buffer);

	
	while(1){

	//sound.setLoop(true);
	sound.play();
	sleep(1);
	sound.stop();

		
	}*/
	//cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	
	/*t1.join();
	t2.join();
	t3.join();
	*/ 
	t4.join();
	
	
    return 0;
}

