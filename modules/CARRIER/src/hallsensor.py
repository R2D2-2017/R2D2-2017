##
#\file
#\brief		This is a module for reading the KY-024 Hall Sensor.
#\author	Robbie Valkenburg and Wilco Louwerse.
#\copyright	Copyright (c) 2017, The R2D2 Team.
#\license	See LICENSE.
#\wiki		https://github.com/R2D2-2017/R2D2-2017/wiki/Keyes-KY-024-Hall-Sensor
#\Trello	https://trello.com/c/5KfmCbD0/6-4-install-the-hal-sensors-so-they-can-detect-the-magnets

# External module imports
import RPi.GPIO as GPIO
import time	
GPIO.setmode(GPIO.BOARD)

##
#\brief A class for reading if the hall sensor detected any form of magnetism.
class HallSensor:
	##
	#\brief Setup HallSensor class with a given pin.
	#
	#\param[in]	pin		the hall sensor pin to be read.
	def __init__(self, pin):
		self.hallSensorPin = pin
		GPIO.setup(self.hallSensorPin, GPIO.IN)
	##
	#\brief This function checks if the hall sensor detected magnetism.
	#
	#\return Returns true if the hall sensor detected magnetism.
	def isMagnetDetected(self):
		return GPIO.input(self.hallSensorPin)
		
# Create hall sensor class
hallSensor = HallSensor(7)

# Loop for testing the hall sensor
while True:
	print(hallSensor.isMagnetDetected())