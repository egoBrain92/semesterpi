#include "ISensor.h"
#include <iostream>

ISensor::~ISensor(){}

int* ISensor::getData(){
	return data;
}

//middle the measurements
int ISensor::calcMidValue(){
	int midValue = 0;
	int i;
	for(i = 0; i< MIDDLE;i++){
		midValue += data[i];
	}
	midValue = midValue/MIDDLE;			
	
	return midValue; 
}
//put measurements in right position in array 
void ISensor::collectMeasurements(){
	data[mmCounter] = calcDistance();
	std::cout<<" dataCounter: "<<data[mmCounter]<<std::endl;
	std::cout<<" mmCounter: "<<mmCounter<<std::endl;
	if(mmCounter >= MIDDLE - 1){
		mmCounter = 0;
	}else{
		mmCounter++;
	}	
}
//push midData from all Sensors to global distance Array. 
void ISensor::pushData(int distances[], int sensorNr, int midDistance){
	distances[sensorNr] = midDistance;	
}


