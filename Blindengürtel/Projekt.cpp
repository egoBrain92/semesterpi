#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "SensorMid.h"
#include "SensorUp.h"
#include "SensorLow.h"

#define NUMBER_OF_SENSORS 3

#define ECHO_PIN_SUP	15
#define ECHO_PIN_SLOW	1
#define ECHO_PIN_SMID	17
#define TRIG_PIN_SUP	16
#define TRIG_PIN_SLOW	4
#define TRIG_PIN_SMID	18

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

		/*distances of all Sensors
		0 : Sensor Up
		1 : Sensor Mid
		2 : Sensor down
		*/
double distances[NUMBER_OF_SENSORS];

//thread function: same function for different threads, just differs in parameter (polymorphy)
void* thread(void* sensor){
	ISensor* mySen = (ISensor*) sensor;
	
	while(1){
		cout<<"newThread"<<endl;
		mySen->collectMeasurements();
		cout<<"	Sensor: "<<mySen->getId()<<endl;
		cout<<"	calcMidValue: "<<mySen->calcMidValue()<<endl;
		pthread_mutex_lock(&mut);
		mySen->pushData(distances, mySen->getId(), mySen->calcMidValue());
		pthread_mutex_unlock(&mut);
		sleep(2);
	}
}

int main()
{	
	

	SensorMid* senMid = new SensorMid(ECHO_PIN_SMID, TRIG_PIN_SMID, 1);
	SensorUp* senUp = new SensorUp(ECHO_PIN_SUP, TRIG_PIN_SUP, 0);
	SensorLow* senLow = new SensorLow(ECHO_PIN_SLOW, TRIG_PIN_SLOW, 2);

	int checkMid;
	int checkLow;
	int checkUp;
	
	//initialize threads
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	
	//create first thread for middle sensor
	checkMid = pthread_create(&t1, NULL, thread, (void*)senMid);
	if(checkMid){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}  
	
	//create second thread for upper sensor
	checkUp = pthread_create(&t1, NULL, thread, (void*)senUp);
	if(checkUp){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}

	checkLow = pthread_create(&t1, NULL, thread, (void*)senLow);
		if(checkLow){
			cout<<"unable to create thread"<<endl;
			exit(-1);
		}
	
	while(1){
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<" / SensorLow: "<<distances[2]<<endl;
		sleep(1);
	}
	
    return 0;
}

