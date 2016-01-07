#ifndef SENSORUP_H_
#define SENSORUP_H_

#include "ISensor.h"


class SensorUp: public ISensor{	
	public:	
		SensorUp(int, int, int);
		~SensorUp(void);
		double calcDistance(int);
	
};
#endif

