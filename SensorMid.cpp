#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>


	
SensorMid::SensorMid(int ePin, int tPin)
: echoPin(ePin), trigPin(tPin){

}

SensorMid::~SensorMid(){

}
			
void* SensorMid::calcDistance(){
	while(1){
		std::cout<<"Distanz"<<std::endl;
		sleep(3);
	}
}			

