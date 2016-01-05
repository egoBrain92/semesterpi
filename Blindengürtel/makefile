all: c a

c: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp 
	g++ Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp AudioPlayer.cpp -lpthread

w: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp
	g++ Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp AudioPlayer.cpp -lpthread -lwireingPi

a:	
	sudo ./a.out

