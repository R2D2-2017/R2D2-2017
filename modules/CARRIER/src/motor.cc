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

void Motor::sendCommand(uint8_t hexCommand, uint8_t speed) {
    uint8_t fullCommand[] = { MotorControls::startBit, MotorControls::deviceId, hexCommand, speed, 0x0 };
    serialPuts(openPort, (char*)fullCommand);
}
