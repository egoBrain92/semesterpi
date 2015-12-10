#ifndef SENSORMID_H_
#define SENSORMID_H_

#include "ISensor.h"



class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int);
		~SensorMid();
		int calcDistance();
		void initiateMeasurement()(int);
				
	private:
		int echoPin;
		int trigPin;
};
#endif
