#include <stdio.h>
#include <unistd.h>
#include <iostream>
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

#define SENSOR_BAD_READ 40000
#define WAIT_FOR_SENESOR 400

#define NUMBER_OF_SENSORS 3
#define INIT_ARRAY_VAL 151

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

void audioFunction(AudioPlayer* ap){
	
	while(1){
		mtx1.lock();
		ap->playSound();
		mtx1.unlock();

		mtx2.lock();
		ap->setPause(intensity * 1000000);
		mtx2.unlock();

		usleep(ap->getPause());
	}
}


int main()
{
	setup();
	long travelTimeUp;
	long travelTimeLow;
	long travelTimeMid;
	
	int soundIndex;
	
	bool checkMid;
	bool checkUp;
	bool checkLow;
	
	int loop1Protector1;
	int loop1Protector2;

	int loop2Protector1;
	int loop2Protector2;
	
	SensorMid* senMid;
	SensorUp* senUp;
	SensorLow* senLow;
	
	AudioPlayer* ap;
	
	//create different sensors
	try{
		senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1);
	}catch(bad_alloc&){
		cout<<"failed to create SensorMid the system will reboot now."<<endl;
		system("sudo reboot");
	}
	
	try{
		senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	}catch(bad_alloc&){
		cout<<"failed to create SensorUp the system will reboot now."<<endl;
		system("sudo reboot");
	}
	
	try{
		senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);
	}catch(bad_alloc&){
		cout<<"failed to create SensorLow the system will reboot now."<<endl;
		system("sudo reboot");
	}
	
	try{
		ap = new AudioPlayer();
	}catch(bad_alloc&){
		cout<<"failed to create AudioPlayer the system will reboot now."<<endl;
		system("sudo reboot");
	}

	//create thread to play acustic signals
	thread audioThread(audioFunction, ap);
	audioThread.detach();
	
	while(1){
		checkMid = false;
		checkUp = false;
		checkLow = false;
		
		senLow->initiateMeasurement();
		senUp->initiateMeasurement();
		senMid->initiateMeasurement();
		
		usleep(WAIT_FOR_SENESOR); //wait for Sensor to react
		
		loop1Protector1 = micros();
		loop1Protector2 = 0;
		
		while(digitalRead(senMid->getEchoPin()) == LOW && digitalRead(senUp->getEchoPin()) == LOW && digitalRead(senLow->getEchoPin()) == LOW){
			loop1Protector2 = abs(micros() - loop1Protector1);
			if(loop1Protector2 > SENSOR_BAD_READ){
				cout<<"1 : "<<loop1Protector2<<endl;
				break; //break from the loop if the sensor did not react properly
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
				break; //break from the loop if the sensor did not react properly
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
		senMid->pushData(distances);
		senUp->pushData(distances);
		senLow->pushData(distances);
	
		usleep(50000); //break between measurements ~20 measurements per second
		
		soundIndex = ap->chooseSoundindex(distances, NUMBER_OF_SENSORS);
	
		mtx1.lock();
		ap->chooseSoundPath();
		mtx1.unlock();

		if(ap->getSoundPair()->soundIndex != -1){
			mtx2.lock();
			intensity = distances[soundIndex]/MAXDISTANCE;
			mtx2.unlock();
		}
	
		//cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	}
	
	audioThread.join();
	
	cout<<"fatal error the system will reboot now."<<endl;
	system("sudo reboot");
	
    return 0;
}

