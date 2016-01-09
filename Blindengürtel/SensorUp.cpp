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
			
double SensorUp::calcDistance(int travelTime){
	//SENUP_ANGLE*M_PI/180 : convert from degree to radiant for function cos
	double distance = cos(SENUP_ANGLE*M_PI / 180.0) * (travelTime/(double)DIV);
	//std::cout<<"distance calc: "<<distance<<" senID: "<<getId()<<std::endl;
	return distance;
}


