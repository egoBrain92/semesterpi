
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
		///Is the echo GPIO pin that is used for this sensor and mapped by the wiringPi.h.
		int echoPin;
		///Is the trigger GPIO pin that the is used for this sensor and mapped by the wiringPi.h.
		int trigPin;
		///Is the id which is used to push the averaged values in the correct position of global the distances[] array.
		int id;
		///Is used to store the measured values in the correct position of the data[] array and also average them.
		int mmCounter;
		///Hold measured values.
		double data[MIDDLE];

		double calcMidValue(void);
	
};

#endif
