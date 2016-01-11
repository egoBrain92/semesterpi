
#ifndef ISENSOR_H_
#define ISENSOR_H_

#define MIDDLE 3	 //number of measurements to middle
#define NOTICE_RANGE 150 //measurement range in cm
#define TAIL_HIGHT 100  //Sensor hight

#define SONIC_SPEED 343 //in m/s

#define DIV 58		//divisor for calculating distance of sonictraveltime in cm



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
		double data[MIDDLE] = {0, 0, 0};

		double calcMidValue(void);
	
};

#endif
