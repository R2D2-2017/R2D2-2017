#include "parser.hh"

Status parseCommand(const hwlib::string<0> &command, RobotArmController &robotArmController) {
    uint8_t space = 0; // the place of the space

    for (; command[space] != ' ' && space < command.length(); space++) // find space
        ;
    if (space == command.length() - 1) return Status::SyntaxError; // cry if no space is found

    const auto start = command.begin();
    const auto end = command.end();
    const hwlib::string<8> action = command.range(start, start + space);
    const hwlib::string<4> amount = command.range(start + space + 1, end);

    int16_t intAmount = 0;
    bool    direction = 0; // true if we go counterclockwise (negative value)

    // string to int routine because no stdlib and not present in hwlib :(
    for (uint8_t i = 0; i < amount.length(); i++) {
        char t = amount[i];

        if (!i) { // only do this the first time
            if (t == '-') {
                direction = true;
                continue;
            }
        }

        if (!(t >= '0' && t <= '9')) return Status::SyntaxError; // no number no parsing

        intAmount *= 10;
        intAmount += t - '0';
    }

    hwlib::cout << action << ' ' << amount << '\n'; // debug output for the parser

    if (action == "X") {
        robotArmController.rotateAxis(RobotAxis::X, intAmount, direction);
        return Status::Succesful;
    }

    if (action == "Y") {
        robotArmController.rotateAxis(RobotAxis::Y, intAmount, direction);
        return Status::Succesful;
    }

    if (action == "Z") {
        robotArmController.rotateAxis(RobotAxis::Z, intAmount, direction);
        return Status::Succesful;
    }

    if (action == "WAIT_S") {
        hwlib::wait_ms(intAmount * 1000);
        return Status::Succesful;
    }

    if (action == "WAIT_MS") {
        hwlib::wait_ms(intAmount);
        return Status::Succesful;
    }

    if (action == "RESET") {
        robotArmController.startup();
        return Status::Succesful;
    }

    return Status::SyntaxError;
}
