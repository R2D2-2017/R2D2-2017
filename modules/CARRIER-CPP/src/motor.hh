#include <wiringSerial>
#include <wiringPi>

struct protocolCommands{
	char startbit = 0xAA;
	char deviceId = 0x0A;
} protocolCommands;

class motor{
private:
	std::string portName;
	int baud;
	int openPort
public:
	motor(std::string portName, int baud);

	void sendCommand(char hexCommand, int speed);

}