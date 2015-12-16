#include <iostream>
#include "SensorLow.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
//#include <wiringPi.h>



SensorLow::SensorLow(int ePin, int tPin, int id)
: echoPin(ePin), trigPin(tPin), id(id){

}

SensorLow::~SensorLow(){

}
void SensorLow::initiateMeasurement(int tPin){
	/*digitalWrite(tPin, LOW);
        delayMicroseconds(5);
        digitalWrite(tPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin, LOW); */
}

double SensorLow::calcDistance(int travelTime){
	double distance = cos(SENLOW_ANGLE*M_PI / 180.0) * (travelTime/(double)DIV);;
	return distance;
}
int SensorLow::getId(){
	return id;
}

