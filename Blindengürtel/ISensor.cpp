#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

ISensor::ISensor(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){

	int i;
	for(i = 0; i < MIDDLE; i++){
		data[i] = 0;
	}
	
	this->mmCounter = 0;
}

ISensor::~ISensor(){}

double ISensor::calcMidValue(){
	int i;
	double midValue = 0;

	for(i = 0; i< MIDDLE;i++){
		midValue += this->data[i];
	}
	midValue = midValue/MIDDLE;			
	
	return midValue; 
}

void ISensor::collectMeasurements(int traveltime){
	data[this->mmCounter] = calcDistance(traveltime);
	
	if(this->mmCounter >= MIDDLE - 1){
		this->mmCounter = 0;
	}else{
		this->mmCounter++;
	}	
}

void ISensor::pushData(double distances[]){
	distances[this->id] = calcMidValue();
}

void ISensor::initiateMeasurement(){    
	digitalWrite(this->trigPin, LOW); 
	//wait for the GPIO to react
	delayMicroseconds(5);
	digitalWrite(this->trigPin, HIGH);
	//wait for the sensor to react if the times is to short the sensor may not trigger
	delayMicroseconds(10); 
	digitalWrite(this->trigPin, LOW); 
}

void ISensor::setupPins(){
	pinMode(this->echoPin, INPUT);
    pinMode(this->trigPin, OUTPUT);
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
