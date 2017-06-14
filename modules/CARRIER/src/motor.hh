/**
 * \file
 * \brief     Main program to control motor
 * \author    Jip Galema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include <wiringSerial.h>
#include <wiringPi.h>
#include <iostream>

/*
 *\brief Serial communication clas with wiringPi
 * Simple class that encapsulates wiringSerial
 * That is able send commands with the protocol required by the Qik2s12v10
*/  
enum MotorControls : char{
	startBit = 0xAA,
    deviceId = 0x0A
};

class Motor{
private:
	/// The port name for the raspberry pi zero w this is "/dev/ttyS0"
	std::string portName;
	/// Baudrate you wat to open the serial connection on
	int baud;
	/// The opened serial port that can be used by wiringSerial
	int openPort;
public:
	/*
     *\brief constructor for Motor class opens the serial for wiringSerial 
     *\param[in] portName path to serial connection port
     *\param[in] baud baudrate you want to open the serial connection on
     */
	Motor(std::string portName, int baud);

	/*
     *\brief function that sends command with given motor speed to serial port
     * with protocol used by Qik2s12v10 
     *\param[in] hexCommand as found in https://github.com/R2D2-2017/R2D2-2017/wiki/%5BCARRIER%5DIndoor-driving-platform
     *\param[in] speed the motors will be turning this number has to be 
	 * between 0 and 127
     */
	void sendCommand(char hexCommand, int speed);
};
