
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
		virtual double calcDistance(int) = 0;
		virtual void initiateMeasurement(int) = 0;
		virtual int getId(void) = 0;
		virtual ~ISensor();

		double calcTravelTime(void);
		double* getData(void);
		double calcMidValue(void);
		int getmmCounter(void);
		void collectMeasurements(void);
		void pushData(double[], int, double);
		

			

	private:
		double data[MIDDLE];
		int mmCounter;
	
};

#endif
