#include <iostream>
#include "SensorLow.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <wiringPi.h>


///Creats an obejct of a sensor for the HC-SR04 which is measureing in a 33° angle downwards.\n
///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
SensorLow::SensorLow(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

SensorLow::~SensorLow(){

}

double SensorLow::calcDistance(int travelTime){
	double distance = cos(SENLOW_ANGLE * M_PI / 180.0) * (travelTime/(double)DIV);
	return distance;
}


