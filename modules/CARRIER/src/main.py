from motor import MotorControl
from enum import Enum
import serial


class States(Enum):
    idle = 1
    driving = 2
    turning = 3
    shutdown = 4

s = serial.Serial("/dev/ttyAMA0", 38400, timeout=0.5)
motor = MotorControl(s)

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

        elif pressed == 's':
            state = States.shutdown
            
        else:
            print("prease pressu da buttonu")
            pressed = input()

    if state == States.driving:
        #sonar goes here

        
        if pressed == 'f':
            motor.forward(63)
            motor.stop()
        elif pressed == 'b':
            motor.reverse(63)
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

    if state == States.shutdown:

        s.close()
        exit()
