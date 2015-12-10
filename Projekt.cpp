#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include "SensorMid.cpp"
#include "SensorUp.cpp"

using namespace std;
void* thread(void* sensor){
	ISensor* b = (ISensor*) sensor;
	b->calcDistance();
}
void* test(void* bla){
	cout<<"test"<<endl;
}
int main()
{	
	SensorMid* senMid = new SensorMid(15,16);
	SensorUp* senUp = new SensorUp(15,16);

	int check1;
	int check2;
	
	
	pthread_t t1;
	pthread_t t2;
	
	check1 = pthread_create(&t1, NULL, thread, (void*)senMid);
	if(check1){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}  
	check1 = pthread_create(&t1, NULL, thread, (void*)senUp);
	if(check1){
		cout<<"unable to create thread"<<endl;
		exit(-1);
	}  
	
	while(1){
		cout<<"wait_main"<<endl;
		sleep(5);
	}
	
    return 0;
}

