#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

///Creats an obejct of a sensor for the HC-SR04 which will measure directly in front of the user.\n
///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
SensorMid::SensorMid(int ePin, int tPin, int sensId)
: ISensor(ePin, tPin, sensId){

}

SensorMid::~SensorMid(){

}
			
double SensorMid::calcDistance(int travelTime){
		double distance = -1;
	//int distance = rand() % 150 + 1;
	   
		//Get distance in cm
		distance = travelTime / DIV;
		//std::cout<<"distance calc: "<<distance<<" senID: "<<getId()<<std::endl;
	
    return distance;
}



			

