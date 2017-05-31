##
#\file
#\brief		This is a module for reading the HC-SR04 Ultrasonic Sensor.
#\author	Mike Hilhorst, David de Jong, Wilco Louwerse, Robbie Valkenburg, Nicky van Steensel van der Aa, Bram van Bergeijk.
#\copyright	Copyright (c) 2017, The R2D2 Team.
#\license	See LICENSE.
#\wiki		https://github.com/R2D2-2017/R2D2-2017/wiki/HC-SR04-Ultrasonic-sensor
#\Trello	https://trello.com/c/FxRxNblW/7-6-make-the-platform-stop-when-the-sonar-sensor-detects-something-within-its-working-area

import RPi.GPIO as GPIO                                 	#Import GPIO library
import time                                                	#Import time library
GPIO.setwarnings(False) 

##
#\brief A class for reading the distance to the closest object measured by the Ultrasonic Sensor.
class Sonar:	
	##
	#\brief Setup Ultrasonic Sensor class with a given trigger and echo pin.
	#
	#\param	triggerPin		The pin used to send signals to the Ultrasonic Sensor.
	#\param	echoPin			The pin used to receive singals from the Ultrasonic Sensor.
	def __init__(self, triggerPin, echoPin):				
			
			self.trigger = triggerPin
			self.echo = echoPin

			GPIO.setup(triggerPin,GPIO.OUT)                 #Set pin as GPIO out
			GPIO.setup(echoPin,GPIO.IN)                     #Set pin as GPIO in
			GPIO.output(triggerPin, False)                  #Set TRIG as LOW 
			time.sleep(0.001)                               #Small delay

	##
	#\brief This function gets the distance to the closest object measured by the Ultrasonic Sensor.
	#
	#\return the distance in cm or a 404 when no object is detected in range.
	def getDistance(self):                                  #Associate the triggerpins 
			
			GPIO.output(self.trigger, True)                 #Set TRIG as HIGH
			time.sleep(0.001)                  	        	#Delay of 0.00001 seconds
			GPIO.output(self.trigger, False)                #Set TRIG as LOW
			
			
			while GPIO.input(self.echo)==0:               	#Check whether the ECHO is LOW
					pulse_start = time.time()               #Saves the last known time of LOW pulse
					
			
			while GPIO.input(self.echo)==1:               	#Check whether the ECHO is HIGH
					pulse_end = time.time()                 #Saves the last known time of HIGH pulse
					
			
			pulse_duration = pulse_end - pulse_start 	#Get pulse duration to a variable
			
			distance = pulse_duration * 17150        	#Multiply pulse duration by 17150 to get distance

			
			if distance > 2 and distance < 400:      	#Check whether the distance is within range
					return int(distance - 0.5)  		#Print distance with 0.5 cm calibration
			else:
					return 404                  		#display out of range

	
