#include "ISensor.cpp"



class SensorMid: public ISensor{	
	public:	
		SensorMid(int, int);
		~SensorMid();
		void* calcDistance();
				
	private:
		int echoPin;
		int trigPin;
};

