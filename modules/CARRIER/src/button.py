"""@
Authors: Robbie Valkenburg and Wilco Louwerse
Wiki: (part of:) https://github.com/R2D2-2017/R2D2-2017/wiki/Carrier-Platform
Trello: https://trello.com/c/R10Cnnf0/5-4-signals-from-the-buttons-are-now-able-to-control-the-platform
This is a test code for reading button presses, using a button class that contains a function (isPressed) to check if a button is pressed.
"""

# External module imports
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

# Button Class
class Button:
"""
A class for one button with a function (isPressed) to check if a button is pressed
"""
	# Constructor requires number of pin
	def __init__(self, pin):
		""" Setup button class with a given pin """
		self.buttonPin = pin
		GPIO.setup(self.buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	# Check if button pressed
	def isPressed(self):
		""" Returns true if the button is pressed """
		return GPIO.input(self.buttonPin)

# Buttons
buttonUp = Button(17)
buttonDown = Button(16)
buttonLeft = Button(17)
buttonRight = Button(18)
lastButton = ""
# Loop for test button
while True:
	if buttonUp.isPressed() and lastButton != "UP":
		print("button up pressed")
                lastButton = "UP"	
	elif buttonDown.isPressed() and lastButton != "DOWN":
		print("button down pressed")
		lastButton = "DOWN"
		
	elif buttonRight.isPressed() and lastButton != "RIGHT":
		print("button right pressed")
		lastButton = "RIGHT"
		
	elif buttonLeft.isPressed() and lastButton != "LEFT":
		print("button left pressed")
		lastButton = "LEFT"
	else:
		print("NOTHING PRESSED \n")




