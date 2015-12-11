#ifndef SENSORUP_H_
#define SENSORUP_H_

#include "ISensor.h"




class SensorUp: public ISensor{	
	public:	
		SensorUp(int, int);
		~SensorUp();
		int calcDistance();
		void initiateMeasurement(int);
				
	private:
		int echoPin;
		int trigPin;
};
#endif

