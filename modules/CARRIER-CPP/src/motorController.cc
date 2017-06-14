#include "motorController.hh"

motorController::motorController(std::string portName, int baud):
	leftMotor(portName, baud),
	rightMotor(portName, baud)
{}

void motorController::forward(int speed){
	leftMotor.sendCommand(0x08, speed);
	rightMotor.sendCommand(0x0C, speed);
}

void motorController::backward(int speed){
	leftMotor.sendCommand(0x0A, speed);
	rightMotor.sendCommand(0x0E, speed);
}

void motorController::left(int speed){
	leftMotor.sendCommand(0x08,0);
	rightMotor.sendCommand(0x0C, speed);
}

void motorController::right(int speed){
	leftMotor.sendCommand(0x08, speed);
	rightMotor.sendCommand(0x0E, 0);
}

void motorController::stop(){
	leftMotor.sendCommand(0x08, 0);
	leftMotor.sendCommand(0x0C, 0);
}
