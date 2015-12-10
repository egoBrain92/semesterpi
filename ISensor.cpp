#include "ISensor.h"


ISensor::~ISensor(){}

int* ISensor::getData(){
	return data;
}

int ISensor::calcMidValue(){
	int midValue = 0;
	int i;
	for(i = 0; i<MIDDLE;i++){
		midValue += data[i];
	}			
	return midValue; 
}

		

