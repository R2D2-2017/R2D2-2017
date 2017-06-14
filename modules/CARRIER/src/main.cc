#include "carrierController.hh"
#include "motor-controller.hh"
#include "serial-com.hh"
#include <wiringPi.h>

int main(void){
	MotorController controller("/dev/ttyS0", 38400);
	SerialCom serialCom("/dev/rfcomm0", 9600);
    Carrier::CarrierController stateMachine{};

	while(serialCom.init() == 0) {
        delay(1000);
    }
    while(true){
        std::string command = serialCom.readCommand();
        if(command != "-1") {
            if(command.find("FORWARD") != std::string::npos) {
                serialCom.write("GOING FORWARD");
				controller.forward(100);
				delay(1000);
				controller.stop();
            } else if(command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
				controller.backward(100);
				delay(1000);
				controller.stop();
            } else if(command.find("LEFT") != std::string::npos) {
				controller.left(100);
				delay(1000);
				controller.stop();
			} else if(command.find("RIGHT") != std::string::npos) {
                serialCom.write("GOING RIGHT");
				controller.right(100);
				delay(1000);
				controller.stop();
            }
            printf("%s", command.c_str());      
        }
    }
}
