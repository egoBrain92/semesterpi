#include "ISensor.h"

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
	return midValue; 
}
//put measurements in right position in array 
void ISensor::collectMeasurements(){
	data[mmCounter] = calcDistance();
	if(mmCounter >= MIDDLE - 1){
		mmCounter = 0;
	}else{
		mmCounter++;
	}	
}

