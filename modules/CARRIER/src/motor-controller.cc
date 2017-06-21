/**
 * \file
 * \brief     Main program to control motor
 * \author    Jip Galema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "motor-controller.hh"
MotorController::MotorController(std::string portName, int baud) :
	leftMotor(portName, baud),
	rightMotor(portName, baud)
{}

void MotorController::forward(int speed){
	leftMotor.sendCommand(MovementControls::ForwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::ForwardMotorTwo, speed);
}

void MotorController::backward(int speed){
	leftMotor.sendCommand(MovementControls::BackwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::BackwardMotorTwo, speed);
}

void MotorController::left(int speed){
	leftMotor.sendCommand(MovementControls::BackwardMotorOne, speed);
	rightMotor.sendCommand(MovementControls::ForwardMotorTwo, speed);
}

void MotorController::right(int speed){
	leftMotor.sendCommand(MovementControls::BackwardMotorTwo, speed);
	rightMotor.sendCommand(MovementControls::ForwardMotorOne, speed);
}

void MotorController::stop(){
	leftMotor.sendCommand(MovementControls::ForwardMotorOne, 0);
	leftMotor.sendCommand(MovementControls::ForwardMotorTwo, 0);
}
