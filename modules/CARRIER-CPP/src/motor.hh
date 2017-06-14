#pragma once
#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>

class motor{
private:
	std::string portName;
	int baud;
	int openPort;
public:
	motor(std::string portName, int baud);

	void sendCommand(char hexCommand, int speed);

};
