#include "ISensor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

///Is used by the inheriting classes to create the sensor object for the HC-SR04.
///@param ePin Is the echo GPIO pin that is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin that the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which is used to push the averaged values in the correct position of the distances[] array.
ISensor::ISensor(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){

	int i;
	for(i = 0; i < MIDDLE; i++){
		data[i] = 0;
	}
	
	this->mmCounter = 0;
	
	
}

///Destroys the created ISensor object.
ISensor::~ISensor(){}

///Averages the measurements of the sensor in the data array.
double ISensor::calcMidValue(){
	int i;
	double midValue = 0;

	for(i = 0; i< MIDDLE;i++){
		midValue += this->data[i];
	}
	midValue = midValue/MIDDLE;			
	
	return midValue; 
}

///Stores measurements in the correct position in the data[] array.
///@param traveltime Is the time which it takes the sonic pulse to travel from the sensor to the obstacle and back.
void ISensor::collectMeasurements(int traveltime){
	data[this->mmCounter] = calcDistance(traveltime);
	
	if(this->mmCounter >= MIDDLE - 1){
		this->mmCounter = 0;
	}else{
		this->mmCounter++;
	}	
}

///Pushes averaged measurments of all sensors to the global distances[] array.
///@param distances[] is the array that holds the averaged measurments
void ISensor::pushData(double distances[]){
	distances[this->id] = calcMidValue();
}

///Trigger the sensor to send 8 ultrasonic pulses (40 kHz) for starting the measurement via GPIO.
void ISensor::initiateMeasurement(){    
        digitalWrite(this->trigPin, LOW); 
		//wait for the GPIO to react
        delayMicroseconds(5);
        digitalWrite(this->trigPin, HIGH);
		//wait for the sensor to react if the times is to short the sensor may not trigger
        delayMicroseconds(5); 
        digitalWrite(this->trigPin, LOW); 
}

///Getter for echoPin.
///@return returns the GPIO echoPin for the sensor mapped by wiringPi
int ISensor::getEchoPin(){
	return this->echoPin;
}

///Getter for trigPin.
///@return returns the GPIO trigPin for the sensor mapped by wiringPi
int ISensor::getTrigPin(){
	return this->trigPin;
}

///Getter for id.
///@return returns the id of the sensor which is set in the constructor
int ISensor::getId(){
	return this->id;
}





