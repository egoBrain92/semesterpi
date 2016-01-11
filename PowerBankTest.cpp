#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <unistd.h>
//#inculde <cmath.h>
//#inculde <cmath>
#include "math.h"
//#include <chrono>

using namespace std;

//unsigned int sleeptime = 1800000000; //30min
unsigned int sleeptime = 300000000; //5min

string getTime(){
	time_t rawtime;
			struct tm * timeinfo;
			char buffer[80];
			
			time (&rawtime);
			timeinfo = localtime(&rawtime);
			
			strftime(buffer,80,"%d-%m-%Y %I:%M:%S\n",timeinfo);
			string str(buffer);
			return str;
}

void delayTimeEasy(){
		//volatile unsigned int max = 4000000000;
		volatile unsigned int max = 5000000; //~25min 
		volatile double result = 0;
		volatile unsigned int i = 1;
		for(volatile unsigned int k; k < max; k++){
			result = sin(k);
			cout << result << endl;
		}
		i = 1;
}

int main(void) {
	

	//delayMicroseconds(0);


       while(1){
		fstream file("1.txt", ios::in | ios::out | ios::app);
		
		if(!file.is_open()){
			
			cout<< "error while opening the file"<<endl;
			
		}else{
			
			
			cout << getTime() <<endl;
			file << getTime();
			file.close();
		}
		delayTimeEasy();
		//usleep(sleeptime);
	}
		
        return 0;
}
