#include "motor-controller.hh"

MotorController::MotorController(std::string portName, int baud) :
	leftMotor(portName, baud),
	rightMotor(portName, baud)
{}

void MotorController::forward(int speed){
	leftMotor.sendCommand(MovementControls::forwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::forwardMotorTwo, speed);
}

void MotorController::backward(int speed){
	leftMotor.sendCommand(MovementControls::backwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::backwardMotorTwo, speed);
}

void MotorController::left(int speed){
	leftMotor.sendCommand(MovementControls::backwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::forwardMotorTwo, speed);
}

void MotorController::right(int speed){
	leftMotor.sendCommand(MovementControls::backwardMotorTwo, speed);
	rightMotor.sendCommand(MovementControls::forwardMotorOne, speed);
}

void MotorController::stop(){
	leftMotor.sendCommand(MovementControls::forwardMotorOne, 0);
	leftMotor.sendCommand(MovementControls::forwardMotorTwo, 0);
}
