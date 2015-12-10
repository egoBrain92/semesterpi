#ifndef ISENSOR_H_
#define ISENSOR_H_
#define MIDDLE 3


class ISensor{
	public:
		virtual void* calcDistance() = 0;
		virtual ~ISensor();
		int* getData();
		int calcMidValue();
			

	private:
		int data[MIDDLE];
		
};

#endif
