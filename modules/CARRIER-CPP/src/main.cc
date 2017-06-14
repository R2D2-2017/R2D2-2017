#include "motorController.hh"
#include <wiringPi.h>

int main(void){
	auto class_object = motorController("/dev/ttyS0", 38400);

	class_object.forward(100);
	delay(1000);
	class_object.left(30);
	delay(200);
	class_object.forward(30);
	delay(1000);
	class_object.backward(30);
	delay(1500);
	class_object.stop();


}
