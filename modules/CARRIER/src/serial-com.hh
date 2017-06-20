/**
 * \file
 * \brief     Main program for carrier control
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>

/**
 * \brief Serial communication class with wiring pi
 * 
 * Simple class that encapsulates wiringSerial
 * that is able read commands with a newline and write data into the serial
 */
class SerialCom {
private:
    /// The command that has been received
    std::string command;
    /// The serial connection which is basically a file open
    int serialPort;
    /// The path to the serial connection like /dev/rfcomm0
    std::string serial;
    /// Baudrate you want to open the serial connection on
    int baud;

public:
    /**
     * \brief Constructor for SerialCom class
     * 
     * \param[in]  serial  path to serial connection port
     * \param[in]  baud    baudrate you want to open the serial connection on
     */
    SerialCom(std::string serial, int baud);

    /**
     * \brief Try to connect to the serial port
     * 
     * \return 0 if can't connect and 1 if connected
     */
    int init();

    /**
     * \brief reads command until new line and returns it as a std::string
     * 
     * \return received command as string
     */
    std::string readCommand();

    /**
     * \brief Write string to connected serial port
     * 
     * \param[in]  data  string you want to be written to the serial port
     */
    void write(std::string data);
};
