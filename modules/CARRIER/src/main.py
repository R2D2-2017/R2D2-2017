from motor import MotorControl
from sonar import Sonar
from hallsensor import HallSensor
from enum import Enum
import RPi.GPIO as GPIO
import serial
import time
GPIO.setmode(GPIO.BCM)


class States(Enum):
    idle = 1
    driving = 2
    turning = 3
    sensing = 4
    shutdown = 5

s = serial.Serial("/dev/ttyAMA0", 38400, timeout=0.5)
motor = MotorControl(s)

echoLocation = Sonar(23, 24) # pin 23 as triggerpin 24 as echopin
hallSensor = HallSensor(5, 27, 22) # pin 27 as red led and 22 as green led

state = States.idle
pressed = 0


while True:
    if state == States.idle:
        #mockup for button input
        
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
            print("prease pressu da buttonu")
            pressed = input()

    if state == States.driving:
  
        if pressed == 'f':
            motor.forward(63)
        elif pressed == 'b':
            motor.reverse(63)
            
        for i in range(0, 10):
            time.sleep(0.2)
            distance = echoLocation.getDistance()
            print(distance)
            if distance < 40:
                break
                
        motor.stop()
        pressed = 0
        state = States.idle

    if state == States.turning:

        if pressed == 'r':
            motor.right(63)
            motor.stop()
        elif pressed == 'l':
            motor.left(63)
            motor.stop()
            
        pressed = 0
        state = States.idle

    if state == States.sensing:
        for i in range(0, 1000):
            hallSensor.isMagnetDetected()
            time.sleep(0.01)

        pressed = 0
        state = States.idle

    if state == States.shutdown:

        s.close()
        exit()
