#include "motor-controller.hh"

MotorController::MotorController(std::string portName, int baud):
	leftMotor(portName, baud),
	rightMotor(portName, baud)
{}

void MotorController::forward(int speed){
	leftMotor.sendCommand(0x08, speed);
	rightMotor.sendCommand(0x0C, speed);
}

void MotorController::backward(int speed){
	leftMotor.sendCommand(0x0A, speed);
	rightMotor.sendCommand(0x0E, speed);
}

void MotorController::left(int speed){
	leftMotor.sendCommand(0x08,0);
	rightMotor.sendCommand(0x0C, speed);
}

void MotorController::right(int speed){
	leftMotor.sendCommand(0x08, speed);
	rightMotor.sendCommand(0x0E, 0);
}

void MotorController::stop(){
	leftMotor.sendCommand(0x08, 0);
	leftMotor.sendCommand(0x0C, 0);
}
