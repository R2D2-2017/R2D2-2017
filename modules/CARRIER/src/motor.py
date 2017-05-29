import serial
import time

class MotorControl:

    def __init__(self, serial):
        self.serialport = serial

    def forward(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
        time.sleep(2)

    def reverse(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))
        time.sleep(2)

    def left(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))
        time.sleep(2)
        
    def right(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
        time.sleep(2)

    def stop(self):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, 0]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0D, 0]))
