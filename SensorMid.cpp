#include <iostream>
#include "SensorMid.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>


	
SensorMid::SensorMid(int ePin, int tPin)
: echoPin(ePin), trigPin(tPin){

}

SensorMid::~SensorMid(){

}

//Send trig pulse
void SensorMid::initiateMeasurement(int tPin){
        digitalWrite(tPin, LOW);
        delayMicroseconds(5);
        digitalWrite(tPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(tPin, LOW); 
}
		
			
int SensorMid::calcDistance(){
	int distance = 0;
    triggerSensor(trigPin);   
        
    //Wait for echo start
    while(digitalRead(echoPin) == LOW);
 
    long startTime = micros();
    
    //Wait for echo end
    while(digitalRead(echoPin) == HIGH);
    
    //calculate travetime
    long travelTime = micros() - startTime;
        
	//get Distance only if distance < "Erkennungsweite"
	if(travelTime < TIMEOUT){
		//Get distance in cm
		distance = travelTime / DIV;
	}
	else{
		distance = 151;
	}
    return distance;
}


			

