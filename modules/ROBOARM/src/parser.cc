#include "parser.hh"

Error parseCommand(hwlib::string<0> command) {
    uint8_t space = 0;

    for (; command[space] < command.length(); space++)
        ;
    if (space == command.length() - 1) return Error::Syntax;

    hwlib::string<8> action;
    for (uint8_t i = 0; i < space; i++) {
        action[i] = command[i];
    }
    hwlib::string<3> amount;
    for (uint8_t i = space; i < command.length(); i++) {
        amount[i] = command[i];
    }

    int intAmount = 0;
    for (auto x : amount) {
        intAmount *= 10;
        intAmount += x - '0';
    }

    if (action == "X") {
        // servoX(intAmount);
        return Error::Succesful;
    }
    if (action == "Y") {
        // servoY(intAmount);
        return Error::Succesful;
    }
    if (action == "Z") {
        // servoZ(intAmount);
        return Error::Succesful;
    }

    return Error::Syntax;
}
