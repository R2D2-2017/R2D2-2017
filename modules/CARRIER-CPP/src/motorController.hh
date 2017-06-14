#pragma once 
#include "motor.hh"


class motorController{
private:
	motor leftMotor;
	motor rightMotor;
public:
	motorController(std::string portName, int baud);

	void forward(int speed);

	void backward(int speed);

	void left(int speed);

	void right(int speed);

	void stop();

};
