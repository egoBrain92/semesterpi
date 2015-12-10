#include <iostream>
#include "SensorUp.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>


	
SensorUp::SensorUp(int ePin, int tPin)
: echoPin(ePin), trigPin(tPin){

}

SensorUp::~SensorUp(){

}
			
void* SensorUp::calcDistance(){
	while(1){
		std::cout<<"Distanz Upper"<<std::endl;
		sleep(5);
	}
}			

