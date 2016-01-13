
#ifndef ISENSOR_H_
#define ISENSOR_H_

#include <wiringPi.h>

///Amount of measurements to average.
#define MIDDLE 5

///Divisor for calculating distance in cm.
#define DIV 58

///Abstract class for the implementation of HC-SR04 ultrasonic rangefinder.
class ISensor{
	public:
		///Is used by the inheriting classes to create the sensor object for the HC-SR04.
		///@param ePin Is the echo GPIO pin that is used for this sensor and mapped by the wiringPi.h.
		///@param tPin Is the trigger GPIO pin that the is used for this sensor and mapped by the wiringPi.h.
		///@param sensId Is the id which is used to push the averaged values in the correct position of the distances[] array.
		ISensor(int ePin, int tPin, int sensId);
		
		///Destroys the created ISensor object.
		~ISensor();
		
		///Inheriting classes must implement this method for there own calculating method.
		virtual double calcDistance(int) = 0;

		///Getter for id.
		///@return returns the id of the sensor which is set in the constructor
		int getId(void);
		
		///Getter for echoPin.
		///@return returns the GPIO echoPin for the sensor mapped by wiringPi
		int getEchoPin(void);
		
		///Getter for trigPin.
		///@return returns the GPIO trigPin for the sensor mapped by wiringPi
		int getTrigPin(void);
		
		///Trigger the sensor to send 8 ultrasonic pulses (40 kHz) for starting the measurement via GPIO.
		void initiateMeasurement(void);
		
		///Stores measurements in the correct position in the data[] array.
		///@param traveltime Is the time which it takes the sonic pulse to travel from the sensor to the obstacle and back.
		void collectMeasurements(int traveltime);
		
		///Pushes averaged measurments of all sensors to the global distances[] array.
		///@param distances[] is the array that holds the averaged measurments
		void pushData(double distances[]);
		
		///GPIO pin setup for this sensor.
		void setupPins();

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

		///Averages the measurements of the sensor in the data array.
		double calcMidValue(void);
	
};

#endif
