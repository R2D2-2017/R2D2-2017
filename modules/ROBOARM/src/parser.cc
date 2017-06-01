#include "parser.hh"

Status parseCommand(hwlib::string<0> command) {
    uint8_t space = 0; // the place of the space

    for (; command[space] != ' ' && space < command.length(); space++) // find space
        ;
    if (space == command.length() - 1) return Status::SyntaxError; // cry if no space is found

    const auto start = command.begin();
    const auto end   = command.end();
    hwlib::string<8> action = command.range(start, start + space - 1);
    hwlib::string<4> amount = command.range(start + space + 1, end);

    int intAmount = 0;
    for (const auto x : amount) {
        intAmount *= 10;
        intAmount += x - '0';
    }

    if (action == "X") {
        // servoX(intAmount);
        return Status::Succesful;
    }

    if (action == "Y") {
        // servoY(intAmount);
        return Status::Succesful;
    }

    if (action == "Z") {
        // servoZ(intAmount);
        return Status::Succesful;
    }

    if (action == "WAIT_MS") {
        hwlib::wait_ms(intAmount);
        return Status::Succesful;
    }

    return Status::SyntaxError;
}
