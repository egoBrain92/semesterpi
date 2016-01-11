#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

ISensor::ISensor(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){
	int i;
	this->mmCounter = 0;
	for(i = 0; i < MIDDLE; i++){
		data[i] = 0;
	}
}

ISensor::~ISensor(){}

//middle the measurements
double ISensor::calcMidValue(){
	int i;
	double midValue = 0;

	for(i = 0; i< MIDDLE;i++){
		midValue += this->data[i];
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
void ISensor::pushData(double distances[]){
	distances[this->id] = calcMidValue();
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





