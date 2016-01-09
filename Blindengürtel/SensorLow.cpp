#include <iostream>
#include "SensorLow.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <wiringPi.h>



SensorLow::SensorLow(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

SensorLow::~SensorLow(){

}

double SensorLow::calcDistance(int travelTime){
	//double distance = cos(SENLOW_ANGLE*M_PI / 180.0) * (travelTime/(double)DIV);
	double distance = -1;
	distance = travelTime / DIV;
	//std::cout<<"distance calc: "<<distance<<" senID: "<<getId()<<std::endl;
	return distance;
}


