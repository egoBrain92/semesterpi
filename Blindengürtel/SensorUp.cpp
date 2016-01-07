#include <iostream>
#include "SensorUp.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <wiringPi.h>

#define SENUP_ANGLE 33


	
SensorUp::SensorUp(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

SensorUp::~SensorUp(){

}
void SensorUp::initiateMeasurement(){
	digitalWrite(this->trigPin, LOW);
        delayMicroseconds(5);
        digitalWrite(this->trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(this->trigPin, LOW); 
}
			
double SensorUp::calcDistance(int travelTime){
	//SENUP_ANGLE*M_PI/180 : convert from degree to radiant for function cos
	double distance = cos(SENUP_ANGLE*M_PI / 180.0) * (travelTime/(double)DIV);
	return distance;
}
int SensorUp::getId(){
	return id;
}

