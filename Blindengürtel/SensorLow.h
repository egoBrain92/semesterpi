#ifndef SENSORLOW_H_
#define SENSORLOW_H_

#include "ISensor.h"

#define SENLOW_ANGLE 33

///Implementation for the sensor that will measure in an 33° angle downwards
class SensorLow: public ISensor{	
	public:	
		SensorLow(int, int, int);
		~SensorLow(void);
		double calcDistance(int);
		
};
#endif

