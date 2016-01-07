#ifndef SENSORMID_H_
#define SENSORMID_H_

#include "ISensor.h"



class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int, int);
		~SensorMid(void);
		double calcDistance(int);
		
		
};
#endif
