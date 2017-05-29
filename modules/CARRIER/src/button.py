# External module imports
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)

# Button Class
class Button:
	# Constructor requires number of pin
	def __init__(self, pin):
		self.buttonPin = pin
		GPIO.setup(self.buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
	# Check if button pressed
	def isPressed(self):
		return GPIO.input(self.buttonPin)

# Buttons
buttonUp = Button(27)
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
		print("nothing is pressed")
