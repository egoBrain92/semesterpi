#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "SensorMid.h"
#include "SensorUp.h"
#include "SensorLow.h"
#include "AudioPlayer.h"
#include "ErrorLogger.h"
#include <thread>
#include <mutex>
#include <SFML/Audio.hpp>
#include <cmath>

///The time after the measurement is considered a bad value in microseconds.
#define SENSOR_BAD_READ 40000
///After a measurement the sensor should not instantly be triggered again.
#define WAIT_SENSOR_COOLDOWN 51000
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
int main(){
	initDistancesArray();
	long travelTimeUp, travelTimeLow, travelTimeMid;
	int soundIndex;
	bool checkMid, checkUp, checkLow;
	//int loopProtector1, loopProtector2;
	int loop1Protector1, loop1Protector2;
	int loop2Protector1, loop2Protector2;
	
	SensorMid* senMid;
	SensorUp* senUp;
	SensorLow* senLow;
	
	AudioPlayer* ap;
	
	//create the sensor objects for getting access to there methods
	try{
		senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1); 
	}catch(bad_alloc&){
		ErrorLogger::writeToLog("Failed to create SensorMid.", ERROR_LOG_PATH);
		//system("sudo reboot");
	}
	try{
		senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	}catch(bad_alloc&){
		ErrorLogger::writeToLog("Failed to create SensorUp.", ERROR_LOG_PATH);
		//system("sudo reboot");
	}
	try{
		senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);
	}catch(bad_alloc&){
		ErrorLogger::writeToLog("Failed to create SensorLow.", ERROR_LOG_PATH);
		//system("sudo reboot");
	}
	
	wiringPiSetup();
	senMid->setupPins();
	senUp->setupPins();
	senLow->setupPins();
	
	try{
		ap = new AudioPlayer();
	}catch(bad_alloc&){
		ErrorLogger::writeToLog("Failed to create AudioPlayer.", ERROR_LOG_PATH);
		//system("sudo reboot");
	}
	
	thread audioThread(audioFunction, ap); //create the audioThread to play sounds in the background
	
	while(1){
		checkMid = false; //reset the check variables for the next loop cycle
		checkUp = false;
		checkLow = false;
		
		senMid->initiateMeasurement(); //start measurements for all sensors
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
				break; //break from the loop if the sensor did not react properly
			}
		}
		
		long startTime = micros();
		
		loop2Protector1 = micros();
		loop2Protector2 = 0;
		
		while(digitalRead(senMid->getEchoPin()) == HIGH || 
			  digitalRead(senUp->getEchoPin()) == HIGH || 
			  digitalRead(senLow->getEchoPin()) == HIGH){
			
			loop2Protector2 = abs(micros() - loop2Protector1);
			if(loop2Protector2 > SENSOR_BAD_READ){
				break; //break from the loop if the sensor did not react properly
			}
			if(digitalRead(senMid->getEchoPin()) == LOW && checkMid == false){ //calculate the traveltime for each sensor
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
		//calculate the distances and store them  in the data[] array of each sensor
		senUp->collectMeasurements(travelTimeUp); 
		senLow->collectMeasurements(travelTimeLow);
		senMid->collectMeasurements(travelTimeMid);
		
		//push averaged data of each sensor into the global distances[] array
		senMid->pushData(distances);
		senUp->pushData(distances);
		senLow->pushData(distances);
	
		usleep(WAIT_SENSOR_COOLDOWN); //break between measurements ~20 measurements per second
		
		soundIndex = ap->chooseSoundindex(distances, NUMBER_OF_SENSORS); //chooses the appropriate soundIndex to play
	
		soundPathMutex.lock();
		ap->chooseSoundPath(); //chooses the appropriate Path to the soundfile that should be played
		soundPathMutex.unlock();

		if(ap->getSoundPair()->soundIndex != -1){ 
			intensityMutex.lock();
			intensity = distances[soundIndex]/MAX_DISTANCE; //unless no sound is played a new intensity is calculated
			intensityMutex.unlock();
		}
		//cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
	}
	//this part should never be reached
	audioThread.join(); 
	ErrorLogger::writeToLog("Waiting for Audiothhread failed.", ERROR_LOG_PATH);
	//system("sudo reboot");
	
    return 0;
}

