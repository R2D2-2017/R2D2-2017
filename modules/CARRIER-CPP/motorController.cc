#include "motorController.hh"

motorController::motorController(std::string portName, int baud):
	leftMotor(portName, baud),
	rightMotor(portName, baud)
{}

motorController::forward(int speed){
	leftMotor.sendCommand(motorCommands.forwardLeft, speed);
	rightMotor.sendCommand(motorCommands.forwardRight, speed);
}

motorController::backward(int speed){
	leftMotor.sendCommand(motorCommands.backwardLeft, speed);
	rightMotor.sendCommand(motorCommands.backwardRight, speed);
}

motorController::left(int speed){
	leftMotor.sendCommand(motorCommands.forwardLeft,0);
	rightMotor.sendCommand(motorCommands.forwardRight, speed);
}

motorController::right(int speed){
	leftMotor.sendCommand(motorCommands.forwardLeft, speed);
	rightMotor.sendCommand(motorCommands.forwardRight, 0);
}

motorController::stop(){
	leftMotor.sendCommand(motorCommands.forwardLeft, 0);
	leftMotor.sendCommand(motorCommands.forwardRight, 0);
}