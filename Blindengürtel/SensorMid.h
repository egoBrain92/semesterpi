#ifndef SENSORMID_H_
#define SENSORMID_H_

#include "ISensor.h"

///Implementation for the sensor that will measure directly in front of the user.
class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int, int);
		~SensorMid(void);
		double calcDistance(int);
		
		
};
#endif
