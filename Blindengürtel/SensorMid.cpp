#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

SensorMid::SensorMid(int ePin, int tPin, int sensId)
: ISensor(ePin, tPin, sensId){

}

SensorMid::~SensorMid(){

}

double SensorMid::calcDistance(int travelTime){
		double distance = 0;
		//Get distance in cm
		distance = travelTime / DIV;
    return distance;
}



			

