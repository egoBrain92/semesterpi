
#ifndef ISENSOR_H_
#define ISENSOR_H_

///Amount of measurements to average.
#define MIDDLE 5

///Divisor for calculating distance in cm.
#define DIV 58

///Abstract class for the implementation of HC-SR04 ultrasonic rangefinder.
class ISensor{
	public:
		ISensor(int, int, int);
		~ISensor();
		
		///Inheriting classes must implement this method for there own calculating method.
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
