# External module imports
import RPi.GPIO as GPIO
import time

# Button Class
class Button:
	# Constructor requires number of pin
	def __init__(self, pin):
		self.buttonPin = pin
		GPIO.setup(buttonUpPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
	# Check if button pressed
	def isPressed(self):
		return GPIO.input(self.buttonPin)

# Buttons
buttonUp = Button(19)
buttonDown = Button(16)
buttonLeft = Button(17)
buttonRight = Button(18)
lastButton = ""

# Loop for test button
while True:
	if buttonUp.isPressed() AND lastButton != "UP":
		print("button up pressed")
		lastButton = "UP"
		
	elif buttonDown.isPressed() AND lastButton != "DOWN":
		print("button down pressed")
		lastButton = "DOWN"
		
	elif buttonRight.isPressed() AND lastButton != "RIGHT":
		print("button right pressed")
		lastButton = "RIGHT"
		
	elif buttonLeft.isPressed() AND lastButton != "LEFT":
		print("button left pressed")
		lastButton = "LEFT"
	else:
		print("nothing is pressed")