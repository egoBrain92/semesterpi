#ifndef SENSORMID_H_
#define SENSORMID_H_

#include "ISensor.h"



class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int, int);
		~SensorMid(void);
		double calcDistance(int);
		void initiateMeasurement(int);
		int getId(void);
				
	private:
		int echoPin;
		int trigPin;
		int id;  //kann id nicht auch in ISensor.h ???? aber wie????
};
#endif
