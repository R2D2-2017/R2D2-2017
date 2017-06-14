#pragma once 
#include "motor.hh"

enum MovementControls : char{
    forwardMotorOne = 0x08,
    forwardMotorTwo = 0x0C,
    backwardMotorOne = 0X0A,
    backwardMotorTwo = 0x0E
};


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
