#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

///abstract class for the HC-SR04 Ultrasonic Rangefinder
ISensor::ISensor(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){
	
	int i;
	
	this->mmCounter = 0;
	
	for(i = 0; i < MIDDLE; i++){
		data[i] = 0;
	}
}


ISensor::~ISensor(){}

///middle the measurements of the sensor in the data array
double ISensor::calcMidValue(){
	int i;
	double midValue = 0;

	for(i = 0; i< MIDDLE;i++){
		midValue += this->data[i];
	}
	midValue = midValue/MIDDLE;			
	
	return midValue; 
}

///store measurements in correct position in data
///@param the time which it takes for the sonic pulse to travel from the sensor to the obstacle and back to the sensor
void ISensor::collectMeasurements(int traveltime){
	data[this->mmCounter] = calcDistance(traveltime);
	
	if(this->mmCounter >= MIDDLE - 1){
		this->mmCounter = 0;
	}else{
		this->mmCounter++;
	}	
}

///pushes middeld measurments of all sensors to the global distances array
///@param distances is the array that holds the middeld measurments
void ISensor::pushData(double distances[]){
	distances[this->id] = calcMidValue();
}

///trigger the sensor to send an ultrasonic impuls for starting the measurement via GPIO
void ISensor::initiateMeasurement(){    
        digitalWrite(this->trigPin, LOW); 
		//wait for the GPIO to react
        delayMicroseconds(5);
        digitalWrite(this->trigPin, HIGH);
		//wait for the sensor to react if the times is to short the sensor may not trigger
        delayMicroseconds(10); 
        digitalWrite(this->trigPin, LOW); 
}

///@return returns the GPIO echoPin for the sensor mapped by wiringPi
int ISensor::getEchoPin(){
	return this->echoPin;
}

///@return returns the GPIO trigPin for the sensor mapped by wiringPi
int ISensor::getTrigPin(){
	return this->trigPin;
}

///@return returns the id of the sensor which is set in the constructor
int ISensor::getId(){
	return this->id;
}





