/**
 * \file
 * \brief     Main program to control motor
 * \author    Jip Galema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "motor.hh"

Motor::Motor(std::string portName, int baud) : portName(portName), baud(baud) {
    openPort = serialOpen(portName.c_str(), baud);
}

void Motor::sendCommand(char hexCommand, int speed) {
    char fullCommand[] = { MotorControls::startBit, MotorControls::deviceId, hexCommand, char(speed), '\0' };
    serialPuts(openPort, fullCommand);
}
