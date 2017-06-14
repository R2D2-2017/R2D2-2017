#include "motor.hh"

Motor::Motor(std::string portName, int baud) : portName(portName), baud(baud) {
    openPort = serialOpen(portName.c_str(), baud);
}

void Motor::sendCommand(char hexCommand, int speed) {
    char fullCommand[] = { MotorControls::startBit, MotorControls::deviceId, hexCommand, char(speed) };
    serialPuts(openPort, fullCommand);
}
