#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <wiringPi.h>
#include "SensorMid.h"
#include "SensorUp.h"
#include "SensorLow.h"
#include "AudioPlayer.h"

#define NUMBER_OF_SENSORS 3

#define ECHO_PIN_SUP	15
#define TRIG_PIN_SUP	16

#define ECHO_PIN_SLOW	1
#define TRIG_PIN_SLOW	4

#define ECHO_PIN_SMID	5
#define TRIG_PIN_SMID	6



pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

		/*distances of all Sensors
		0 : Sensor Up
		1 : Sensor Mid
		2 : Sensor down
		*/
double distances[NUMBER_OF_SENSORS];

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
void* thread(void* sensor){
	ISensor* mySen = (ISensor*) sensor;

	while(1){
		//cout<<"newThread"<<endl;
		mySen->collectMeasurements();
		usleep(50000);
		cout<<"	Sensor: "<<mySen->getId()<<endl;
		//cout<<"	calcMidValue: "<<mySen->calcMidValue()<<endl;
		pthread_mutex_lock(&mut);
		mySen->pushData(distances, mySen->getId(), mySen->calcMidValue());
		pthread_mutex_unlock(&mut);
		//sleep(2);
	}
}

void* apFunction(void* audioPlayer){
	string sound;
	AudioPlayer* ap = (AudioPlayer*) audioPlayer;
	while(1){

		pthread_mutex_lock(&mut);
		sound = ap->chooseSound(distances, NUMBER_OF_SENSORS)->soundPath;
		pthread_mutex_unlock(&mut);
		//cout<<"soundpath: "<<sound<<endl;
		if(sound != NO_SOUND){

			pthread_mutex_lock(&mut);
			ap->setPause(ap->calcIntensity(distances[ap->getSoundPair()->soundIndex], MAXDISTANCE));
			pthread_mutex_unlock(&mut);

			ap->playSound(ap->getSoundPair()->soundPath);
			usleep(ap->getPause()*1000000);
			cout<<"sound: "<<sound<<endl;
		}
	}
}

int main()
{
	setup();
	soundPair* sp = new soundPair;
	AudioPlayer* ap = new AudioPlayer(1, sp);

	SensorMid* senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1);
	//SensorUp* senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	//SensorLow* senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);

	int checkMid;
	int checkLow;
	int checkUp;
	int checkAP;

	//initialize threads
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t audioThread;

	//create first thread for middle sensor
	checkMid = pthread_create(&t1, NULL, thread, (void*)senMid);
	if(checkMid){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}

	/*//create second thread for upper sensor
	checkUp = pthread_create(&t2, NULL, thread, (void*)senUp);
	if(checkUp){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}

	checkLow = pthread_create(&t3, NULL, thread, (void*)senLow);
		if(checkLow){
			cout<<"unable to create thread"<<endl;
			exit(-1);
		}
	*/
	/*checkAP = pthread_create(&audioThread, NULL, apFunction, (void*)ap);
		if(checkAP){
			cout<<"unable to create thread"<<endl;
			exit(-1);
	}*/
	while(1){
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
		sleep(1);
	}

    return 0;
}

