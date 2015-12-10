all: c a

c: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp
	g++ Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp -lpthread

a:	
	sudo ./a.out

