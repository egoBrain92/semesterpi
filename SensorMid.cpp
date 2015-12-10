#include <iostream>
#include "SensorMid.h"
#ifndef SENSORMID_CPP_
#define SENSORMID_CPP_


	
SensorMid::SensorMid(int ePin, int tPin)
: echoPin(ePin), trigPin(tPin){

}

SensorMid::~SensorMid(){

}
			
void* SensorMid::calcDistance(){
	while(1){
		std::cout<<"Distanz"<<std::endl;
	}
}			
 #endif
