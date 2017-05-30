import serial


class MotorControl:

    def __init__(self, serial):
        self.serialport = serial

    def forward(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))
  

    def reverse(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))


    def left(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0E, speed]))

        
    def right(self, speed):
        self.serialport.write(bytes([0xAA, 0x0A, 0x0A, speed]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0C, speed]))


    def stop(self):
        self.serialport.write(bytes([0xAA, 0x0A, 0x08, 0]))
        self.serialport.write(bytes([0xAA, 0x0A, 0x0D, 0]))
