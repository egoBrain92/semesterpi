#ifndef ISENSOR_H_
#define ISENSOR_H_

#define MIDDLE 3

#define TIMEOUT 9000
#define DIV 58


class ISensor{
	public:
		virtual int calcDistance() = 0;
		virtual void initiateMeasurement() = 0;
		virtual ~ISensor();
		int* getData();
		int calcMidValue();
			

	private:
		int data[MIDDLE];
		
};

#endif
