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

///The time after the measurement is considered a bad value in microseconds.
#define SENSOR_BAD_READ 40000
///After a measurement the sensor should not instantly be triggered again.
#define WAIT_SENSOR_COOLDOWN 50000
///Delay duration that is needed after initiating the measurements in microseconds.
#define WAIT_FOR_SENSORS 400
///One second in microseconds.
#define ONE_SECOND 1000000
///The number of sensors that are connected to the pi.
#define NUMBER_OF_SENSORS 3
///Initial values for the distances[NUMBER_OF_SENSORS] array so the first few measurements don't create bad output.
#define INIT_ARRAY_VAL 151
///Echo pin of the sensor that will measure in an 33° angle upwards.
#define ECHO_PIN_SUP	15
///Trigger pin of the sensor that will measure in an 33° angle upwards.
#define TRIG_PIN_SUP	16
///Echo pin of the sensor that will measure in an 33° angle downwards.
#define ECHO_PIN_SLOW	1
///Trigger pin of the sensor that will measure in an 33° angle downwards.
#define TRIG_PIN_SLOW	4
///Echo pin for the sensor that will measure directly in front of the user.
#define ECHO_PIN_SMID	5
///Trigger pin for the sensor that will measure directly in front of the user.
#define TRIG_PIN_SMID	6

using namespace std;

///Is used to protect the soundPath from the main and AudioPlayer thread.
mutex soundPathMutex;
///Is used to protect the intensity from the main and AudioPlayer thread.
mutex intensityMutex;

/*distances of all Sensors
0 : Sensor Up
1 : Sensor Mid
2 : Sensor down*/

///Holds the averaged values of the measurements.
double distances[NUMBER_OF_SENSORS];

///Stores the duration of the silence in between two sound outputs.
double intensity;	

///Initiate the values of the distances[] array with INIT_ARRAY_VAL.
void initDistancesArray(){
	for(int i = 0; i < NUMBER_OF_SENSORS; i++){
		distances[i] = INIT_ARRAY_VAL;
	}
}

///Sets the GPIO pins for all sensors.
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

///Used for the thread audioThread which will play sounds in the background.
///@param ap is the AudioPlayer Object that is used to play and load sounds.
void audioFunction(AudioPlayer* ap){
	
	while(1){
		soundPathMutex.lock();
		ap->playSound();
		soundPathMutex.unlock();

		intensityMutex.lock();
		ap->setPause(intensity * ONE_SECOND);
		intensityMutex.unlock();

		usleep(ap->getPause());
	}
}

///core of the programm
int main()
{
	initDistancesArray();
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
		
		senMid->initiateMeasurement();
		senLow->initiateMeasurement();
		senUp->initiateMeasurement();
		
		usleep(WAIT_FOR_SENSORS); //wait for Sensor to react
		
		loop1Protector1 = micros();
		loop1Protector2 = 0;
		
		while(digitalRead(senMid->getEchoPin()) == LOW && 
			  digitalRead(senUp->getEchoPin()) == LOW && 
			  digitalRead(senLow->getEchoPin()) == LOW){
				  
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
		
		while(digitalRead(senMid->getEchoPin()) == HIGH || 
			  digitalRead(senUp->getEchoPin()) == HIGH || 
			  digitalRead(senLow->getEchoPin()) == HIGH){
			
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

		senUp->collectMeasurements(travelTimeUp);
		senLow->collectMeasurements(travelTimeLow);
		senMid->collectMeasurements(travelTimeMid);
		
		//push averaged data of each sensor 
		senMid->pushData(distances);
		senUp->pushData(distances);
		senLow->pushData(distances);
	
		usleep(WAIT_SENSOR_COOLDOWN); //break between measurements ~20 measurements per second
		
		soundIndex = ap->chooseSoundindex(distances, NUMBER_OF_SENSORS);
	
		soundPathMutex.lock();
		ap->chooseSoundPath();
		soundPathMutex.unlock();

		if(ap->getSoundPair()->soundIndex != -1){
			intensityMutex.lock();
			intensity = distances[soundIndex]/MAX_DISTANCE;
			intensityMutex.unlock();
		}
	
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	}
	
	audioThread.join();
	
	cout<<"fatal error the system will reboot now."<<endl;
	system("sudo reboot");
	
    return 0;
}

