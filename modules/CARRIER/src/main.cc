#include "carrier-controller.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include <wiringPi.h>

int main(void){
	MotorController controller("/dev/ttyS0", 38400);
	SerialCom serialCom("/dev/rfcomm0", 9600);
    Carrier::CarrierController stateMachine{ controller };

	while(serialCom.init() == 0) {
        delay(1000);
    }
    while(true){
        std::string command = serialCom.readCommand();
        if(command != "-1") {
            if(command.find("FORWARD") != std::string::npos) {
                serialCom.write("GOING FORWARD");
				stateMachine.forward(100);
            } else if(command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
                stateMachine.backward(100);
            } else if(command.find("LEFT") != std::string::npos) {
				stateMachine.left(100);
			} else if(command.find("RIGHT") != std::string::npos) {
                serialCom.write("GOING RIGHT");
                stateMachine.right(100);
            }
            printf("%s", command.c_str());      
        }
        stateMachine.update();
    }
}
