#include "serial-com.hh"

SerialCom::SerialCom(std::string serial, int baud) : serial(serial), baud(baud) {

}

int SerialCom::init() {
    std::cout << "Connecting to serial: " << serial << "\n";
    serialPort = serialOpen(serial.c_str(), baud);
    serialFlush(serialPort);
    if(serialPort < 0) {
        std::cout << "Can't connect to serial port: " << serial << "\n";
        return 0;
    } else {
        std::cout << "Connected to serial port: " << serial << "\n";     
        return 1;          
    }
    return 0;
}

std::string SerialCom::readCommand() {
    command = "";
    while(serialDataAvail(serialPort)) {
        char c = serialGetchar(serialPort);
        if(isalpha(c)) {
            command += c;
        }
    }
    if(command.length() > 2) {
        return command;
    } else {
        return "-1";
    }
}

void SerialCom::write(std::string c) {
    printf("HELP");
    serialPrintf(serialPort, c.c_str());
}

SerialCom::~SerialCom() {
    serialClose(serialPort);
}