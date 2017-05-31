##
#\file
#\brief		This is a module for controlling the motors.
#\author	Mike Hilhorst, David de Jong, Wilco Louwerse.
#\copyright	Copyright (c) 2017, The R2D2 Team.
#\license	See LICENSE.
#\wiki		...
#\Trello(1)	https://trello.com/c/KL8lOZvJ/2-4-allowing-control-of-the-engines-as-to-spin-them-forwards-and-backwards
#\Trello(2) https://trello.com/c/N8kg309G/3-1-allowing-the-engines-to-be-set-to-spin-in-opposite-directions-so-the-platform-can-turn

import serial
import time

##
#\brief A class for controlling the motors to be able to make the platfom move forward, backward, stop it and make it turn.
class MotorControl:
	##
	#\brief Setup MotorControl class with a given serial port.
	#
	#\param	serial		The given serial port used for writing assignments to the motors.
    def __init__(self, serial):
        self.serialport = serial

	##
	#\brief This function makes both motors rotate forward with a given speed, making the platfom move forward.
	#
	# ...info over bits die verzonden worden...
	#\param	speed		[0-127], The speed at which both the motors will rotate forward.
    def forward(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
  
	##
	#\brief This function makes both motors rotate backward with a given speed, making the platfom move backward.
	#
	# ...info over bits die verzonden worden...
	#\param	speed		[0-127], The speed at which both the motors will rotate backward.
    def reverse(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))

	##
	#\brief This function makes the right motor rotate forward and the left motor backward, both with the same given speed. This makes the platfom turn left.
	#
	# ...info over bits die verzonden worden...
	#\param	speed		[0-127], The speed at which both the motors will rotate.
    def left(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))
		time.sleep(2)

    ##
	#\brief This function makes the left motor rotate forward and the right motor backward, both with the same given speed. This makes the platfom turn right.
	#
	# ...info over bits die verzonden worden...
	#\param	speed		[0-127], The speed at which both the motors will rotate.
    def right(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
		time.sleep(2)

	##
	#\brief This function sets both motors speed to 0, stopping the platform from moving.
	#
	# ...info over bits die verzonden worden...
    def stop(self):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, 0]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0D, 0]))
