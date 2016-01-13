all: c a

c: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp 
	g++ Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp AudioPlayer.cpp -lpthread

w: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp
	g++ -w Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp AudioPlayer.cpp -lpthread -lwiringPi

wa: Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp
	g++ -Wall -std=c++11 Projekt.cpp ISensor.cpp SensorMid.cpp SensorUp.cpp SensorLow.cpp AudioPlayer.cpp ErrorLogger.cpp -lpthread -lwiringPi -lsfml-audio 
	sudo ./a.out

a:	
	sudo ./a.out

test: AudioPlayerTest.cpp AudioPlayer.cpp
	g++ -std=c++11 AudioPlayerTest.cpp AudioPlayer.cpp -lsfml-audio -lcppunit

