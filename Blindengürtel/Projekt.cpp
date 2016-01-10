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
#include <cmath>

#define NO_SOUND "NOSOUND"
#define SOUND_UPPER "sound3.wav"
#define SOUND_MID "sound4.wav"
#define SOUND_LOWER "LowKurzerTon.wav"
#define ERROR_SOUND "ErrorkurzerTon.wav"
#define SENSOR_BAD_READ 40000


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
}

void myFunction(){
	sf::SoundBuffer sb1;
	sf::SoundBuffer sb2;
	sf::SoundBuffer sb3;
	sf::Sound sound;
	double sleepTimer;
	
	sb1.loadFromFile(SOUND_UPPER);
	sb2.loadFromFile(SOUND_LOWER);
	sb3.loadFromFile(SOUND_MID);
	
	
	while(1){
		if(soundPath == SOUND_UPPER){
			sound.setBuffer(sb1);
			sound.play();
		}
		
		if(soundPath == SOUND_LOWER){
			sound.setBuffer(sb2);
			sound.play();
		}
		
		if(soundPath == SOUND_MID){
			sound.setBuffer(sb3);
			sound.play();
		}
		mtx2.lock();
		sleepTimer = intensity;
		mtx2.unlock();
		
		usleep(sleepTimer * 1000000);
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
	
	int loop1Protector1;
	int loop1Protector2;

	int loop2Protector1;
	int loop2Protector2;

	SensorMid* senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1);
	SensorUp* senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	SensorLow* senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);
	
	thread audioThread(myFunction);
	audioThread.detach();
	
	while(1){
		//cout<<"micros(): "<<micros()<<endl;
		checkMid = false;
		checkUp = false;
		checkLow = false;
		
		senLow->initiateMeasurement();
		senUp->initiateMeasurement();
		senMid->initiateMeasurement();
		
		usleep(400); //wait for Sensor to react
		
		loop1Protector1 = micros();
		loop1Protector2 = 0;
		
		while(digitalRead(senMid->getEchoPin()) == LOW && digitalRead(senUp->getEchoPin()) == LOW && digitalRead(senLow->getEchoPin()) == LOW){
			loop1Protector2 = abs(micros() - loop1Protector1);
			if(loop1Protector2 > SENSOR_BAD_READ){
				cout<<"1 : "<<loop1Protector2<<endl;
				break; //break from the loop if the senesor did not react properly
			}
			//cout<<"1 : "<<loop1Protector2<<endl;
		}
		
		long startTime = micros();
		
		loop2Protector1 = micros();
		loop2Protector2 = 0;
		
		while(digitalRead(senMid->getEchoPin()) == HIGH || digitalRead(senUp->getEchoPin()) == HIGH || digitalRead(senLow->getEchoPin()) == HIGH){
			
			loop2Protector2 = abs(micros() - loop2Protector1);
			//cout<<"2 : "<<loop2Protector2<<endl;
			if(loop2Protector2 > SENSOR_BAD_READ){
				cout<<"2 : "<<loop2Protector2<<endl;
				break; //break from the loop if the senesor did not react properly
			}
			//usleep(50);
			if(digitalRead(senMid->getEchoPin()) == LOW && checkMid == false){
				travelTimeMid = abs(micros() - startTime);
				checkMid = true;
			}
			if(digitalRead(senUp->getEchoPin()) == LOW && checkUp == false){
				travelTimeUp = abs(micros() - startTime);
				checkUp = true;
			}
			if(digitalRead(senLow->getEchoPin()) == LOW && checkLow == false){
				travelTimeLow = (micros() - startTime);
				checkLow = true;
			}		
		}

		senMid->collectMeasurements(travelTimeMid);
		senUp->collectMeasurements(travelTimeUp);
		senLow->collectMeasurements(travelTimeLow);
		
		//push middled data of each sensor 
		senMid->pushData(distances, senMid->getId(), senMid->calcMidValue());
		senUp->pushData(distances, senUp->getId(), senUp->calcMidValue());
		senLow->pushData(distances, senLow->getId(), senLow->calcMidValue());
	
		usleep(50000); //break between measurements ~20 Measurements per secound
		
	
	soundIndex = -1;
	distance = MAXDISTANCE;

	for(i = 0; i < NUMBER_OF_SENSORS; i++){
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
	
		//cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	}
	
	audioThread.join();
	
    return 0;
}

