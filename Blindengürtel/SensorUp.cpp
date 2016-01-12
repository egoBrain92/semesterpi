#include <iostream>
#include "SensorUp.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <wiringPi.h>

///Creats an obejct of a sensor for the HC-SR04 which is measureing in a 33° angle upwards.\n
///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
SensorUp::SensorUp(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

SensorUp::~SensorUp(){

}
			
double SensorUp::calcDistance(int travelTime){
	//SENUP_ANGLE*M_PI/180 : convert from degree to radiant for function cos
	double distance = cos(SENUP_ANGLE * M_PI / 180.0) * (travelTime/(double)DIV);
	//std::cout<<"distance calc: "<<distance<<" senID: "<<getId()<<std::endl;
	return distance;
}


