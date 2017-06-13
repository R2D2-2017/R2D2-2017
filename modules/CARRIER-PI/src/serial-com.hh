#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>

class SerialCom {
    private:
        std::string command;
        int serialPort;
        std::string serial;
        int baud;
    public:
        SerialCom(std::string serial, int baud);
        int init();
        ~SerialCom();
        std::string readCommand();
        void write(std::string c);
};