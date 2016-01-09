
#ifndef ISENSOR_H_
#define ISENSOR_H_

#define MIDDLE 3	 //number of measurements to middle
#define NOTICE_RANGE 150 //measurement range in cm
#define TAIL_HIGHT 100  //Sensor hight

#define SONIC_SPEED 343 //in m/s


//#define TIMEOUT 9000
#define DIV 58		//divisor for calculating distance of sonictraveltime in cm



class ISensor{
	public:
		ISensor(int, int, int);
		virtual double calcDistance(int) = 0;
		int getId(void);
		int getEchoPin(void);
		int getTrigPin(void);
		~ISensor();
		
		void initiateMeasurement(void);
		double calcTravelTime(void);
		double* getData(void);
		double calcMidValue(void);
		int getmmCounter(void);
		void collectMeasurements(int);
		void pushData(double[], int, double);
		
		double data[MIDDLE] = {0, 0, 0};

			

	private:
		int echoPin;
		int trigPin;
		int id;
		int mmCounter;
	
};

#endif
