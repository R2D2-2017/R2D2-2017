<<<<<<< HEAD
#include "carrier-controller.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include <wiringPi.h>


int main(void){
	int statusLed = 29;
	MotorController controller("/dev/ttyS0", 38400);
	SerialCom serialCom("/dev/rfcomm0", 9600);
  	wiringPiSetup();
	pinMode (statusLed, OUTPUT) ;
    Carrier::CarrierController stateMachine(controller, 100, 50);
	while(serialCom.init() == 0) {
		digitalWrite (statusLed, 1) ;     // On
        delay(1000);
		digitalWrite (statusLed, 0) ;     // off		
    }
	digitalWrite (statusLed, 1) ;     // On
    while(true){
        std::string command = serialCom.readCommand();
        if(command != "-1") {
            if(command.find("FORWARD") != std::string::npos) {
				stateMachine.forward(100);
                serialCom.write("GOING FORWARD");                
            } else if(command.find("BACKWARD") != std::string::npos) {
                stateMachine.backward(100);
                serialCom.write("GOING BACKWARD");
            } else if(command.find("LEFT") != std::string::npos) {
				stateMachine.left(100);
                serialCom.write("GOING LEFT");
			} else if(command.find("RIGHT") != std::string::npos) {
                stateMachine.right(100);
                serialCom.write("GOING RIGHT");
            } else if(command.find("STOP") != std::string::npos) {
                stateMachine.stop();
                serialCom.write("STOPPING");
            }
            
            printf("%s", command.c_str());      
        }
    }
}