#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

ISensor::~ISensor(){}

double* ISensor::getData(){
	return data;
}

//middle the measurements
double ISensor::calcMidValue(){
	double midValue = 0;
	int i;
	for(i = 0; i< MIDDLE;i++){
		midValue += data[i];
	}
	midValue = midValue/MIDDLE;			
	
	return midValue; 
}
//put measurements in right position in array 
void ISensor::collectMeasurements(int echoPin){
	std::cout<<"collectMeasurement: "<<echoPin<<std::endl;
	data[mmCounter] = calcDistance(calcTravelTime(echoPin));
	//std::cout<<" dataCounter: "<<data[mmCounter]<<std::endl;
	std::cout<<" mmCounter: "<<mmCounter<<std::endl;
	
	if(mmCounter >= MIDDLE - 1){
		mmCounter = 0;
	}else{
		mmCounter++;
	}	
}
//push midData from all Sensors to global distance Array. 
void ISensor::pushData(double distances[], int sensorNr, double midDistance){
	distances[sensorNr] = midDistance;	
	std::cout<<"pushdata: "<<sensorNr<<std::endl;
}

double ISensor::calcTravelTime(int echoPin){
	//Wait for echo start
		initiateMeasurement();
		std::cout<<"calcTravelTime: PIN: "<<echoPin<<std::endl;
		std::cout<<"calc PIN: "<<this->echoPin<<std::endl;
		while(digitalRead(echoPin) == LOW);

		long startTime = micros();
		std::cout<<"calc PIN: "<<echoPin<<std::endl;
		//Wait for echo end
		while(digitalRead(echoPin) == HIGH);

		//calculate travetime
		long travelTime = micros() - startTime;
		
		//double travelTime = rand() % 25000;
		return travelTime;
}




