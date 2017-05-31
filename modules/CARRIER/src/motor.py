##
#\file
#\brief		This is a module for controlling the motors.
#\author	Mike Hilhorst, David de Jong, Wilco Louwerse
#\copyright	Copyright (c) 2017, The R2D2 Team.
#\license	See LICENSE.
#\wiki		...
#\Trello	...

import serial
import time

##
#\brief ...
class MotorControl:
	##
	#\brief ...
	#
	#\param	serial		...
    def __init__(self, serial):
        self.serialport = serial

	##
	#\brief ...
	#
	#\param	speed		...
    def forward(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
  
	##
	#\brief ...
	#
	#\param	speed		...
    def reverse(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))

	##
	#\brief ...
	#
	#\param	speed		...
    def left(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))
		time.sleep(2)

    ##
	#\brief ...  
	#
	#\param	speed		...
    def right(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
		time.sleep(2)

	##
	#\brief ...
    def stop(self):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, 0]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0D, 0]))
