#include "motor-controller.hh"
#include "serial-com.hh"
#include <wiringPi.h>


int main(void){
	int statusLed = 29;
	MotorController controller("/dev/ttyS0", 38400);
	SerialCom serialCom("/dev/rfcomm0", 9600);
	std::string currentCommand = "";
  	wiringPiSetup();
	pinMode (statusLed, OUTPUT) ;
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
                serialCom.write("GOING FORWARD");
				controller.forward(100);
				delay(100);
				controller.stop();
            } else if(command.find("BACKWARD") != std::string::npos) {
                serialCom.write("GOING BACKWARD");
				controller.backward(100);
				delay(100);
				controller.stop();
            } else if(command.find("LEFT") != std::string::npos) {
				controller.left(100);
				delay(100);
				controller.stop();
			} else if(command.find("RIGHT") != std::string::npos) {
                serialCom.write("GOING RIGHT");
				controller.right(100);
				delay(100);
				controller.stop();
            }
            printf("%s", command.c_str());      
        }
    }
}
