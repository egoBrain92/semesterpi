#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>


	
SensorMid::SensorMid(int ePin, int tPin, int sensId)
: ISensor(ePin, tPin, sensId){

}

SensorMid::~SensorMid(){

}
			
double SensorMid::calcDistance(int travelTime){
		double distance = -1;
	//int distance = rand() % 150 + 1;
	   
		//Get distance in cm
		distance = travelTime / DIV;
		std::cout<<"distance calc: "<<distance<<" senID: "<<getId()<<std::endl;
	
    return distance;
}



			

