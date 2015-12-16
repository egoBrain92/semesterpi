#ifndef SENSORLOW_H_
#define SENSORLOW_H_

#define SENLOW_ANGLE 33

#include "ISensor.h"




class SensorLow: public ISensor{	
	public:	
		SensorLow(int, int, int);
		~SensorLow(void);
		double calcDistance(int);
		void initiateMeasurement(int);
		int getId(void);
				
	private:
		int echoPin;
		int trigPin;
		int id;
};
#endif

