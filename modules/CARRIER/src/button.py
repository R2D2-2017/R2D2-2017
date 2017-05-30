"""
\file
\brief		This is a module for reading button presses.
\author		Robbie Valkenburg and Wilco Louwerse.
\copyright	Copyright (c) 2017, The R2D2 Team.
\license	See LICENSE.
\Trello		https://trello.com/c/R10Cnnf0/5-4-signals-from-the-buttons-are-now-able-to-control-the-platform
"""

# External module imports
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)

class Button:
"""
\brief A class for reading presses of one button.
"""
	def __init__(self, pin):
		""" 
		\brief Setup button class with a given pin.
		
		\param[in]	pin		the button pin to be read.
		"""
		self.buttonPin = pin
		GPIO.setup(self.buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
	def isPressed(self):
		""" 
		\brief This function checks if the button is pressed.
		
		\return Returns true if the button is pressed.
		"""
		return GPIO.input(self.buttonPin)

# Create button classes
buttonUp = Button(17)
buttonDown = Button(16)
buttonLeft = Button(17)
buttonRight = Button(18)
lastButton = ""

# Loop for testing the buttons
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




