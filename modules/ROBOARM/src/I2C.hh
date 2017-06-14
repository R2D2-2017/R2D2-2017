/**
 * \file
 * \author    Matthijs Vos
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"

class I2C {

	hwlib::i2c_bus &i2c_bus;


	/**
	* Size of the list that is always set to 2, commands are always 2 bytes.
	*/
	static const int size = 2;

    uint8_t slaveAdress;
	
public:
	/**
	* Sets the I2C-bus
	*/
	I2C(hwlib::i2c_bus &i2c_bus);

	/**
	* Runs a small demo to make a led blink
	*/
	void runDemo();

	/**
	* sends command tothe slave
	*/
	void sendCommand(uint8_t registerAdress,uint8_t registerValues);
	
	


};