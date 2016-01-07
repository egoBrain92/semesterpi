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

//Send trig pulse
/*void SensorMid::initiateMeasurement(){
		
		std::cout<<"this->trig"<<this->trigPin<<std::endl;
		std::cout<<"this->echo"<<this->echoPin<<std::endl;
        //std::cout<<"tpin Para"<<tPin<<std::endl;
        
        digitalWrite(this->trigPin, LOW);
        delayMicroseconds(5);
        digitalWrite(this->trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(this->trigPin, LOW); 
        
}*/
			
double SensorMid::calcDistance(int travelTime){
		double distance = -1;
	//int distance = rand() % 150 + 1;
	   
		//Get distance in cm
		distance = travelTime / DIV;
		std::cout<<"distance calc:"<<distance<<"senID: "<<getId()<<std::endl;
	
    return distance;
}
int SensorMid::getId(){
	return id;
}


			

