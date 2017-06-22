/**
 * \file
 * \brief     Main program for carrier control
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "serial-com.hh"

SerialCom::SerialCom(std::string serial, int baud) : serial(serial), baud(baud) {}

bool SerialCom::init() {
    std::cout << "Connecting to serial: " << serial << "\n";
    serialPort = serialOpen(serial.c_str(), baud);
    serialFlush(serialPort);
    if(serialPort < 0) {
        std::cout << "Can't connect to serial port: " << serial << "\n";
        return false;
    } else {
        std::cout << "Connected to serial port: " << serial << "\n";
        return true;
    }
}

std::string SerialCom::readCommand() {
    command = "";
    while(serialDataAvail(serialPort)) {
        char c = serialGetchar(serialPort);
        if(isalpha(c)) {
            command += c;
        }
    }
    if(command.length() > 2) {
        return command;
    } else {
        return "-1";
    }
}

void SerialCom::write(std::string data) {
    serialPrintf(serialPort, data.c_str());
}
