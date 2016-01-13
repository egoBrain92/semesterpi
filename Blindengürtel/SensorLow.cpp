#include <iostream>
#include "SensorLow.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <wiringPi.h>

SensorLow::SensorLow(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

SensorLow::~SensorLow(){

}

double SensorLow::calcDistance(int travelTime){
	double distance = cos(SENLOW_ANGLE * M_PI / DEGREE_TO_RADIANT_VALUE) * (travelTime/(double)DIV);
	return distance;
}
