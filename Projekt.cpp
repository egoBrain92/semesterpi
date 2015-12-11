#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "SensorMid.h"
#include "SensorUp.h"

#define NUMBER_OF_SENSORS 3 

using namespace std;

		/*distances of all Sensors
		0 : Sensor Up
		1 : Sensor Mid
		2 : Sensor down
		*/
int distances[NUMBER_OF_SENSORS];

void* thread(void* sensor){
	ISensor* mySen = (ISensor*) sensor;
	
	while(1){
		cout<<"newThread"<<endl;
		mySen->collectMeasurements();
		cout<<"	Sensor: "<<mySen->getId()<<endl;
		cout<<"	calcMidValue: "<<mySen->calcMidValue()<<endl;
		
		mySen->pushData(distances, mySen->getId(), mySen->calcMidValue());
		sleep(2);
	}
}

int main()
{	
	

	SensorMid* senMid = new SensorMid(15, 16, 1);
	SensorUp* senUp = new SensorUp(15, 16, 0);

	int check1;
	int check2;
	
	
	pthread_t t1;
	pthread_t t2;
	
	check1 = pthread_create(&t1, NULL, thread, (void*)senMid);
	if(check1){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}  
	check1 = pthread_create(&t1, NULL, thread, (void*)senUp);
	if(check1){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}  
	
	while(1){
		cout<<"SensorUp: "<<distances[0]<<" / SensorMid: "<<distances[1]<<endl;
		sleep(5);
	}
	
    return 0;
}

