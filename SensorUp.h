#include "ISensor.cpp"

#ifndef SENSORUP_H_
#define SENSORUP_H_



class SensorUp: public ISensor{	
	public:	
		SensorUp(int, int);
		~SensorUp();
		void* calcDistance();
				
	private:
		int echoPin;
		int trigPin;
};

#endif /* SENSORUP_H_ */
