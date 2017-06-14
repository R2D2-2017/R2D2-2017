#include "motor.hh"

motor::motor(std::string portName, int baud):
	portName(portName),
	baud(baud)
	{
		openPort = serialOpen(portName, baud);
	}

void motor::sendCommand(char hexCommand, int speed){
	char fullCommand[] = {	protocolCommands.startbit, protocolCommands.deviceId, 
							hexCommand, char(speed)}
	serialPuts(openPort, fullCommand);
}




