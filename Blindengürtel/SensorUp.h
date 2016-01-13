#ifndef SENSORUP_H_
#define SENSORUP_H_

#include "ISensor.h"

///The angel in which the sensor is mounted.
#define SENUP_ANGLE 33
///Fix value for calulation degree values from the cos() to radient values.
#define DEGREE_TO_RADIANT_VALUE 180.0

///Implementation for the sensor that will measure in an 33° angle upwards	
class SensorUp: public ISensor{	
	public:	
		SensorUp(int, int, int);
		~SensorUp(void);
		double calcDistance(int);
	
};
#endif
