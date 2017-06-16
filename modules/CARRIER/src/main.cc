#include "carrier-controller.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include "hc-sr04.hh"
#include "./states/i-carrier-state.hh"
#include <wiringPi.h>


int main(void) {
    int statusLed = 29;
    int trigger   =  4;
    int echo      =  5;


    MotorController controller("/dev/ttyS0", 38400);
    SerialCom       serialCom("/dev/rfcomm0", 9600);
    HcSr04          sonarSensor(trigger,echo);

    wiringPiSetup();
    pinMode(statusLed, OUTPUT);
    Carrier::CarrierController stateMachine(controller, sonarSensor, 50, 50);

    while (serialCom.init() == 0) {
        digitalWrite(statusLed, 1); // On
        delay(1000);
        digitalWrite(statusLed, 0); // off
    }
    digitalWrite(statusLed, 1); // On

    while (true) {
        std::string command = serialCom.readCommand();
        if (command != "-1") {
            if (command.find("FORWARD") != std::string::npos) {
                serialCom.write("GOING FORWARD");
                stateMachine.setState(Carrier::CarrierState::Forward);
            } else if (command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
                stateMachine.setState(Carrier::CarrierState::Backward);
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
