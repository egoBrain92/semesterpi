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
void ISensor::collectMeasurements(){
	//std::cout<<"collectMeasurement: "<<echoPin<<std::endl;
	data[mmCounter] = calcDistance(calcTravelTime());
	//std::cout<<" dataCounter: "<<data[mmCounter]<<std::endl;
	//std::cout<<" mmCounter: "<<mmCounter<<std::endl;
	
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

double ISensor::calcTravelTime(){
	//Wait for echo start
		initiateMeasurement();
		//std::cout<<"calcTravelTime: "<<echoPin<<std::endl;
		//std::cout<<"calc PIN: "<<this->echoPin<<std::endl;
		while(digitalRead(this->echoPin) == LOW);
		delayMicroseconds(5);
		long startTime = micros();
		
		//Wait for echo end
		while(digitalRead(this->echoPin) == HIGH);
		delayMicroseconds(5);
		//calculate travetime
		long travelTime = micros() - startTime;
		
		//double travelTime = rand() % 25000;
		//usleep(50000);
		return travelTime;
}

void ISensor::initiateMeasurement(){
	//std::cout<<"this->trig"<<this->trigPin<<std::endl;
	//std::cout<<"this->echo"<<this->echoPin<<std::endl;
        
        
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





