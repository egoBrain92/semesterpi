#ifndef SENSORUP_H_
#define SENSORUP_H_

#include "ISensor.h"

#define SENUP_ANGLE 33

///Implementation for the sensor that will measure in an 33° angle upwards	
class SensorUp: public ISensor{	
	public:	
		SensorUp(int, int, int);
		~SensorUp(void);
		double calcDistance(int);
	
};
#endif

