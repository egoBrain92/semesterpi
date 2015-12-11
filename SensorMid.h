#ifndef SENSORMID_H_
#define SENSORMID_H_

#include "ISensor.h"



class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int, int);
		~SensorMid();
		int calcDistance();
		void initiateMeasurement(int);
		int getId();
				
	private:
		int echoPin;
		int trigPin;
		int id;  //kann id nicht auch in ISensor.h ???? aber wie????
};
#endif
