
#ifndef ISENSOR_H_
#define ISENSOR_H_

#define MIDDLE 5	 //number of measurements to middle

#define DIV 58		//divisor for calculating distance of sonictraveltime in cm

///abstract class for the implementation of HC-SR04 Ultrasonic Rangefinder 
class ISensor{
	public:
		ISensor(int, int, int);
		~ISensor();

		virtual double calcDistance(int) = 0;

		int getId(void);
		int getEchoPin(void);
		int getTrigPin(void);
		
		void initiateMeasurement(void);
		void collectMeasurements(int);
		void pushData(double[]);

	private:
		int echoPin;
		int trigPin;
		int id;
		int mmCounter;
		double data[MIDDLE];

		double calcMidValue(void);
	
};

#endif
