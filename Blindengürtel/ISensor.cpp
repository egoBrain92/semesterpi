#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

ISensor::ISensor(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){

	this->mmCounter=0;
	std::cout<<"id: "<<id<<" data: "<<&data<<std::endl;
	std::cout<<"id: "<<this->id<<" data: "<<&(this->data)<<std::endl;
}

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
void ISensor::collectMeasurements(int traveltime){
	data[this->mmCounter] = calcDistance(traveltime);
	if(this->mmCounter >= MIDDLE - 1){
		this->mmCounter = 0;
	}else{
		this->mmCounter++;
	}	
}
//push middled Data of all Sensors to global distance array
void ISensor::pushData(double distances[], int sensorNr, double midDistance){
	distances[sensorNr] = midDistance;	
}

//make the sensor send an ultrasonic impuls for starting the measurement
void ISensor::initiateMeasurement(){    
        digitalWrite(this->trigPin, LOW);
        delayMicroseconds(5);
        digitalWrite(this->trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(this->trigPin, LOW); 
}

int ISensor::getEchoPin(){
	return this->echoPin;
}

int ISensor::getTrigPin(){
	return this->trigPin;
}
int ISensor::getId(){
	return this->id;
}





