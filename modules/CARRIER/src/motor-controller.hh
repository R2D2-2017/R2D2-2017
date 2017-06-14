#pragma once 
#include "motor.hh"


class MotorController{
private:
	Motor leftMotor;
	Motor rightMotor;
public:
	MotorController(std::string portName, int baud);

	void forward(int speed);

	void backward(int speed);

	void left(int speed);

	void right(int speed);

	void stop();

};
