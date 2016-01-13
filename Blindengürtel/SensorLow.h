#ifndef SENSORLOW_H_
#define SENSORLOW_H_

#include "ISensor.h"

///The angel in which the sensor is mounted.
#define SENLOW_ANGLE 33
///Fix value for calulation degree values from the cos() to radient values.
#define DEGREE_TO_RADIANT_VALUE 180.0

///Implementation for the sensor that will measure in an 33° angle downwards.
class SensorLow: public ISensor{	
	public:
	
		///Creats an obejct of SensorLow for the HC-SR04 which is measureing in an 33° angle downwards.\n
		///@param ePin Is the echo GPIO pin the is used for this sensor and mapped by the wiringPi.h.
		///@param tPin Is the trigger GPIO pin the is used for this sensor and mapped by the wiringPi.h.
		///@param sensId Is the id which used to push the averaged values in the correct position of the distances[] array.
		SensorLow(int ePin, int tPin, int id);
		
		///Destroys the created SensorLow object.
		~SensorLow(void);
		
		///Calculates and returns the distance to an obstacle using the travelTime measured by the sensor.\n
		///Uses the cos function from cmath.h to convert degree to radiant values.
		///@param traveltime Is the time which it takes the sonic pulse to travel from the sensor to the obstacle and back.
		///@return Returns the calculated distance. 
		double calcDistance(int travelTime);
		
};
#endif
