#pragma once
#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>

class Motor{
private:
	std::string portName;
	int baud;
	int openPort;
public:
	Motor(std::string portName, int baud);
	void sendCommand(char hexCommand, int speed);
};
