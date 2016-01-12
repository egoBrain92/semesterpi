#include <iostream>
#include "SensorUp.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <wiringPi.h>

///Creats an obejct of SensorUp for the HC-SR04 which is measureing in an 33° angle upwards.\n
///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
SensorUp::SensorUp(int ePin, int tPin, int id)
: ISensor(ePin, tPin, id){

}

///Destroys the created SensorUp object.
SensorUp::~SensorUp(){

}

///Calculates and returns the distance to an obstacle using the travelTime measured by the sensor.\n
///Uses the cos() function from cmath.h to convert degree to radiant values.
///@param traveltime Is the time which it takes the sonic pulse to travel from the sensor to the obstacle and back.
///@return Returns the calculated distance. 
double SensorUp::calcDistance(int travelTime){
	double distance = cos(SENUP_ANGLE * M_PI / DEGREE_TO_RADIANT_VALUE) * (travelTime/(double)DIV);
	return distance;
}