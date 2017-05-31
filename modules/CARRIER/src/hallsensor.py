##
#\file
#\brief		This is a module for reading the KY-024 Hall Sensor.
#\author	Robbie Valkenburg, Wilco Louwerse and Mike Hilhorst.
#\copyright	Copyright (c) 2017, The R2D2 Team.
#\license	See LICENSE.
#\wiki		https://github.com/R2D2-2017/R2D2-2017/wiki/Keyes-KY-024-Hall-Sensor
#\Trello	https://trello.com/c/5KfmCbD0/6-4-install-the-hal-sensors-so-they-can-detect-the-magnets

# External module imports
import RPi.GPIO as GPIO
import time	
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False) 

##
#\brief A class for reading if the hall sensor detected any form of magnetism.
class HallSensor:

        ##
        #\brief Setup HallSensor class with a given pin.
        #
        #\param[in]	pin		the hall sensor pin to be read.
        def __init__(self, pin, ledOne, ledTwo):
                self.hallSensorPin = pin
                self.ledOne = ledOne
                self.ledTwo = ledTwo

                GPIO.setup(self.hallSensorPin, GPIO.IN)
                GPIO.setup(self.ledOne, GPIO.OUT)
                GPIO.setup(self.ledTwo, GPIO.OUT)
        ##
        #\brief This function checks if the hall sensor detected magnetism.
        #
        #\return Returns true if the hall sensor detected magnetism.

        def isMagnetDetected(self):
                if GPIO.input(self.hallSensorPin): # == True
                        GPIO.output(self.ledOne, 0)
                        GPIO.output(self.ledTwo, 1)
                        time.sleep(0.2)
                else:
                        GPIO.output(self.ledOne, 1)
                        GPIO.output(self.ledTwo, 0)

                



    
