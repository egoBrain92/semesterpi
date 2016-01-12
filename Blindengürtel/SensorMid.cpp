#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

///Creats an obejct of SensorMid for the HC-SR04 which will measure directly in front of the user.\n
///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
SensorMid::SensorMid(int ePin, int tPin, int sensId)
: ISensor(ePin, tPin, sensId){

}

///Destroys the created SensorMid object.
SensorMid::~SensorMid(){

}

///Calculates and returns the distance to an obstacle using the travelTime measured by the sensor.\n
///Uses DIV to divide travelTime which results to the distance in centimeter.
///@param traveltime Is the time which it takes the sonic pulse to travel from the sensor to the obstacle and back.
///@return Returns the calculated distance.
double SensorMid::calcDistance(int travelTime){
		double distance = 0;
		//Get distance in cm
		distance = travelTime / DIV;
    return distance;
}



			

