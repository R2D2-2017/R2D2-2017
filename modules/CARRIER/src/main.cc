#include "carrier-controller.hh"
#include "hallsensor.hh"
#include "hc-sr04.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include "hc-sr04.hh"
#include "./states/i-carrier-state.hh"
#include <wiringPi.h>

int main(void) {
    // Wiringpi pin setup
    wiringPiSetup();

    // Pin configuration - https://pinout.xyz/pinout/wiringpi
    int statusLed = 29;
    int trigger   =  4;
    int echo      =  5;
    int hallPin   =  8;

    //Declaration of the system classes
    MotorController                  controller("/dev/ttyS0", 38400);
    SerialCom                        serialCom("/dev/rfcomm0", 9600);
    HcSr04                           sonarSensor(trigger, echo);
    Carrier::CarrierController       stateMachine(controller, sonarSensor, 50);

    // Quick bluetooth status led
    pinMode(statusLed, OUTPUT);

    //If not connected to bluetooth serial blink and poll to connect
    while (serialCom.init() == 0) {
        digitalWrite(statusLed, 1); // On
        delay(1000);
        digitalWrite(statusLed, 0); // off
    }
    digitalWrite(statusLed, 1); // On

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
            }
            printf("%s", command.c_str());
        }
        stateMachine.update();
        delay(100);
    }
}
