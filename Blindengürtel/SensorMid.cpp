#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
//#include <wiringPi.h>


	
SensorMid::SensorMid(int ePin, int tPin, int sensId)
: echoPin(ePin), trigPin(tPin), id(sensId){

}

SensorMid::~SensorMid(){

}

//Send trig pulse
void SensorMid::initiateMeasurement(int tPin){
      /*  digitalWrite(tPin, LOW);
        delayMicroseconds(5);
        digitalWrite(tPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin, LOW); */
}
			
double SensorMid::calcDistance(int travelTime){
	int distance = rand() % 150 + 1;
    /*initiateMeasurement(trigPin);
	   
	//get Distance only if distance < "Erkennungsweite"
	if(travelTime < TIMEOUT){
		//Get distance in cm
		distance = travelTime / DIV;
	}
	else{
		distance = NOTICE_RANGE + 1;
	}*/
    return distance;
}
int SensorMid::getId(){
	return id;
}


			

