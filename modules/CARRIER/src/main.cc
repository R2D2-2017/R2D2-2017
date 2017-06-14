#include <wiringPi.h>
//#include <wiringSerial.h>

struct commands{
	char startbit = 0xAA;
	char deviceID = 0x0A;
	char forwardMotorOne = 0x08;
	char forwardMotorTwo = 0x0C;
	char backwardMotorOne = 0x0A;
	char backwardMotorTwo = 0x0E;
	char speed = 10;
};

/*
class Qik
{
private:
	int port;
	char startbit = 0xAA;
	char deviceID = 0x0A;
	char forwardMotorOne = 0x08;
	char speed = 10;
public:
	Qik(const char * name, int baudrate):
		port(serialOpen(name, baudrate))
	{}
	
	void sendForward(){
		serialPuts(port,&startbit);
		serialPuts(port,&deviceID);
		serialPuts(port,&forwardMotorOne);
		serialPuts(port,&speed);
	}

};*/

int main(void){
	wiringPiSetup();
	pinMode(5, OUTPUT);
	for(int i = 0; i < 10; i++){
		digitalWrite(5,HIGH) ; delay(500);
		digitalWrite(5,LOW) ; delay(500);
	}
	
	//auto object_1 = Qik("ttyAMA0", 19200);
	//object_1.sendForward();

	return 0;

}
