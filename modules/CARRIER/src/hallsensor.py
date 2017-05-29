# External module imports
import RPi.GPIO as GPIO
import time	
	
class HallSensor:

	def __init__(self, pin):
		self.hallSensorPin = pin
		GPIO.setup(hallSensorPin, GPIO.IN)
		
	def isMagnetDetected(self):
		return return GPIO.input(hallSensorPin)
		
hallSensor = HallSensor(15)
hallSensor.isMagnetDetected()