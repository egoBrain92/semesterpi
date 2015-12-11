#include <iostream>
#include "SensorUp.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>


	
SensorUp::SensorUp(int ePin, int tPin)
: echoPin(ePin), trigPin(tPin){

}

SensorUp::~SensorUp(){

}
void SensorUp::initiateMeasurement(int tPin){
	digitalWrite(tPin, LOW);
        delayMicroseconds(5);
        digitalWrite(tPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin, LOW); 
}
			
int SensorUp::calcDistance(){
	sleep(5);
	return 5;
}			

