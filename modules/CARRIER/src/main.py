##
#\file
#\brief     This file cntains the state machien that controlles the Rosbee via the raspberry Pi
#\author    Mike Hilhorst, David de Jong, Wilco Louwerse, Robbie Valkenburg, Nicky van Steensel van der Aa, Bram van Bergeijk
#\copyright Copyright (c) 2017, The R2D2 Team.
#\license   See LICENSE.

from motor import MotorControl                  #Import Motor Controller
from sonar import Sonar                         #Import Sonar Controller
from hallsensor import HallSensor               #Import HallSenor Controller
from enum import Enum                           #Import Enum
import RPi.GPIO as GPIO                         #Import GPIO lib
import serial                                   #Import serial lib
import time                                     #Import time lib

GPIO.setmode(GPIO.BCM)                          #Set board in BCM layout

##
#\brief A enum class that contains the various states of the statemachine 
class States(Enum):                     
	idle = 1
	driving = 2
	turning = 3
	sensing = 4
	shutdown = 5
# Baudrate used in the serial communication
baudRate = 38400

# Serialport for communication with the rosbee motor controller 
s = serial.Serial("/dev/ttyAMA0", baudRate, timeout=0.5)

# Making object with the correct pins
motor = MotorControl(s)                         # Serialport
echoLocation = Sonar(23, 24)                    # Pin 23 as triggerpin 24 as echopin
hallSensor = HallSensor(5, 27, 22)              # Pin 27 as red led and 22 as green led

# The motor speed
motorSpeed = 63

# The range the sonar has to stop at
sonarDetectionRange = 40

# The times the hallsensor reads
halReadAmmount = 1000

# Statemachien default
state = States.idle
pressed = 0

# The time used for delays
sleepTime = 0.2
halSleepTime = 0.01

##
#\brief The statemachine
while True:
	if state == States.idle:
		if pressed == 'f':
			state = States.driving
		elif pressed == 'b':
			state = States.driving
		elif pressed == 'r':
			state = States.turning
		elif pressed == 'l':
			state = States.turning
		elif pressed == 'h':
			state = States.sensing
		elif pressed == 's':
			state = States.shutdown	
		else:
			print("please press one of the folowing keys: 'f' 'b' 'r' 'l' 'h' 's'")       #Input
			pressed = input()

	if state == States.driving:                     # Drive state
  
		if pressed == 'f':                          # Forwards
			motor.forward(motorSpeed)           # Set motor speed 
		elif pressed == 'b':                        # Backwards
			motor.reverse(motorSpeed)
			
		for i in range(0, 10):
			time.sleep(sleepTime)
			distance = echoLocation.getDistance()   # Get sonar value
			print(distance)
			if distance < sonarDetectionRange:      # If the carrier is closer than sonarDetectionRange in cm the loop will break
				break
				
		motor.stop()                                # If the loop in finished or broken the motor stops
		pressed = 0                                 # Back to default values
		state = States.idle                         # Back to default values
	
	if state == States.turning:                     # Turning state

		if pressed == 'r':                          # Right
			motor.right(motorSpeed)                 
			motor.stop()                            # Stop
		elif pressed == 'l':                        # Left
			motor.left(motorSpeed)
			motor.stop()                            # Stop
			
		pressed = 0                                 # Back to default values
		state = States.idle                         # Back to default values

	
	if state == States.sensing:                     #Hallsensor state
		for i in range(0, halReadAmmount):                    
			hallSensor.isMagnetDetected()           # Make green led turn on when magneticfield is found, default red turned on
			time.sleep(halSleepTime)

		pressed = 0                                 # Back to default values
		state = States.idle                         # Back to default values
		
	
	if state == States.shutdown:                    # Shutdown protocol               

		s.close()                                   # Closes the serialport
		exit()                                      # Exits the command line
