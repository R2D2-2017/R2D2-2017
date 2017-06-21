/**
 * \file
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \author    Jip Galema
 * \author    Jan Halsema
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include <wiringPi.h>
#include <vector>
#include "carrier-controller.hh"
#include "hallsensor.hh"
#include "hc-sr04.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include "hc-sr04.hh"
#include "./states/i-carrier-state.hh"
#include "slit-sensor.hh"

int main(void) {
    // Wiringpi pin setup
    wiringPiSetup();

    // Pin configuration - https://pinout.xyz/pinout/wiringpi
    int statusLed = 29;

    int northTrigger   =  4;
    int northEcho      =  5;

    int eastTrigger   =  25;
    int eastEcho      =  24;

    int southTrigger   =  0;
    int southEcho      =  7;

    int westTrigger   =  27;
    int westEcho      =  28;

    int hallPin   =  8;

    //Declaration of the system classes
    MotorController                  controller("/dev/ttyS0", 38400);
    SerialCom                        serialCom("/dev/rfcomm0", 9600);
    std::vector<HcSr04> sonarSensors = {
        HcSr04(northTrigger, northEcho),
        HcSr04(eastTrigger, eastEcho),
        HcSr04(southTrigger, southEcho),
        HcSr04(westTrigger, westEcho)
    };
    Carrier::CarrierController       stateMachine(controller, serialCom, sonarSensors, 127);

    // Quick bluetooth status led
    pinMode(statusLed, OUTPUT);

    //If not connected to bluetooth serial blink and poll to connect
    while (!serialCom.init()) {
        digitalWrite(statusLed, 1); // On
        delay(500);
        digitalWrite(statusLed, 0); // off
        delay(500);
    }
    digitalWrite(statusLed, 1); // On

    // this functionality can't be used yet
    SlitSensor rotationCounter(5,6,1ns);

    //When connected go into the carrier state loop
    while (true) {
        //Read command from the bluetooth serial com
        std::string command = serialCom.readCommand();
        if (command != "-1") {
            if (command.find("FORWARD") != std::string::npos) {
                serialCom.write("GOING FORWARD");
                stateMachine.setState(Carrier::CarrierState::Forward);
            } else if (command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
                stateMachine.setState(Carrier::CarrierState::Backward);
            } else if (command.find("LEFT") != std::string::npos) {
                serialCom.write("GOING COUNTER ClOCKWISE");
                stateMachine.setState(Carrier::CarrierState::CounterClockwise);
            } else if (command.find("RIGHT") != std::string::npos) {
                serialCom.write("GOING CLOCKWISE");
                stateMachine.setState(Carrier::CarrierState::Clockwise);
            } else if (command.find("STOP") != std::string::npos) {
                serialCom.write("STOPPING");
                stateMachine.setState(Carrier::CarrierState::Idle);
            } else if(command.find("AUTO") != std::string::npos){
                serialCom.write("AUTO-DRIVING MODE ACTIVATED");
                stateMachine.setState(Carrier::CarrierState::Auto);
            }
            printf("%s", command.c_str());
        }
        stateMachine.update();
        delay(100);
    }
}
