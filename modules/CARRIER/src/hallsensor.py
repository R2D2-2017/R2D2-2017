# External module imports
import RPi.GPIO as GPIO
import time	
GPIO.setmode(GPIO.BOARD)
#class HallSensor
class HallSensor:
	# Constructor for giving input pin
	def __init__(self, pin):
		self.hallSensorPin = pin
		GPIO.setup(self.hallSensorPin, GPIO.IN)
	# Return status of magnet detection	
	def isMagnetDetected(self):
		return GPIO.input(self.hallSensorPin)
		
# Test code		
hallSensor = HallSensor(7)
while True:
	print(hallSensor.isMagnetDetected())