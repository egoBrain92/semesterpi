all: c a

c: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp
	g++ Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp -lpthread -lwiringPi

a:	
	sudo ./a.out

