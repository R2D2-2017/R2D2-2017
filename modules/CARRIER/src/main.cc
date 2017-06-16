#include "carrier-controller.hh"
#include "hallsensor.hh"
#include "hc-sr04.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include <wiringPi.h>


int main(void) {
    int statusLed = 29;
    int trigger   =  4;
    int echo      =  5;
    int hallPin   =  3;

    wiringPiSetup();

    MotorController controller("/dev/ttyS0", 38400);
    SerialCom       serialCom("/dev/rfcomm0", 9600);
    HcSr04          sonarSensor(trigger, echo);
    HallSensor      hallSensor(hallPin);

    pinMode(statusLed, OUTPUT);
    Carrier::CarrierController stateMachine(controller, sonarSensor, 50, 50);

    // test
    while (true) {
        std::cout << hallSensor.rotations() << '\n';
        if (hallSensor.rotations() > 3) hallSensor.reset();
    }

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
                stateMachine.forward(100);
            } else if (command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
                stateMachine.backward(100);
            } else if (command.find("LEFT") != std::string::npos) {
                serialCom.write("GOING LEFT");
                stateMachine.left(100);
            } else if (command.find("RIGHT") != std::string::npos) {
                serialCom.write("GOING RIGHT");
                stateMachine.right(100);
            } else if (command.find("STOP") != std::string::npos) {
                serialCom.write("STOPPING");
                stateMachine.stop();
            }

            printf("%s", command.c_str());
        }
        stateMachine.update();
        delay(100);
    }
}
