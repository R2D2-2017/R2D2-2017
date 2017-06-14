/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "serial-com.hh"
using namespace std;
int main() {
    SerialCom serialCom("/dev/rfcomm0", 9600);
    while(serialCom.init() == 0) {
        delay(1000);
    }
    while(true){
        string command = serialCom.readCommand();
        if(command != "-1") {
            if(command.find("FORWARD") != string::npos) {
                serialCom.write("GOING FORWARD");
            } else if(command.find("BACKWARD") != string::npos) {
                serialCom.write("GOING BACKWARD");
            } else if(command.find("LEFT") != string::npos) {
                serialCom.write("GOING LEFT");
            } else if(command.find("RIGHT") != string::npos) {
                serialCom.write("GOING RIGHT");
            }
            printf("%s", command.c_str());      
        }
    }
    return 0;
}
