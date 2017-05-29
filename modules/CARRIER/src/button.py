# External module imports
import RPi.GPIO as GPIO
import time

# Mockup for stateMachine
class StateMachine:
	def driveForward(self):
		print("FORWARD")

	def driveBackward(self):
		print("BACKWARD")	

	def rotateLeft(self):
		print("LEFT")

	def rotateRight(self):
		print("RIGHT")

	def idle(self):
		print("IDLE")

#button Class
class Button:
	# Constructor requires number of pin
	def __init__(self, pin):
		self.buttonPin = pin
		GPIO.setup(buttonUpPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

	def isPressed(self):
		return GPIO.input(self.buttonPin)

# Instance of state machine
state = StateMachine()

# Buttons
buttonUp = Button(15)
buttonDown = Button(16)
buttonLeft = Button(17)
buttonRight = Button(18)

# Loop
while True:
	if buttonUp.isPressed():
		state.driveForward()
	elif buttonDown.isPressed():
		state.driveBackward()
	elif buttonRight.isPressed():
		state.rotateRight()
	elif buttonLeft.isPressed():
		state.rotateLeft()
	else:
		state.idle()