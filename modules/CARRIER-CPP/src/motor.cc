#include "motor.hh"

motor::motor(std::string portName, int baud):
	portName(portName),
	baud(baud)
	{
		openPort = serialOpen(portName.c_str(), baud);
	}

void motor::sendCommand(char hexCommand, int speed){
	char fullCommand[] = {	0xAA,0x0A, hexCommand, char(speed)};
	serialPuts(openPort, fullCommand);
}




