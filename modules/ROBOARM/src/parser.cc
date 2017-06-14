/**
 * \file
 * \author    Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "parser.hh"

using namespace RoboArm::Parser;

bool RoboArm::Parser::equal(const hwlib::string<0> &l, const char *r, unsigned int len) {
    if (l.length() == len) {
        for (unsigned int i = 0; i < l.length(); ++i) {
            if (l[i] != r[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

Status RoboArm::Parser::parseCommand(const hwlib::string<0> &command,
                                     RobotArmController &robotArmController) {
    size_t space = 0; // the place of the space

    // find space
    for (; space < command.length() && command[space] != ' '; space++);
    if (space == command.length() - 1)
        return Status::SyntaxError; // cry if no space is found

    const auto start = command.begin();
    const auto end = command.end();
    const hwlib::string<8> action = command.range(start, start + space);
    const hwlib::string<4> amount = command.range(start + space + 1, end);

    int16_t intAmount = 0;
    bool direction = 0; // true if we go counterclockwise (negative value)

    // string to int routine because no stdlib and not present in hwlib :(
    for (size_t i = 0; i < amount.length(); i++) {
        char t = amount[i];

        if (!i) { // only do this the first time
            if (t == '-') {
                direction = true;
                continue;
            }
        }
        // no number no parsing
        if (!(t >= '0' && t <= '9')) return Status::SyntaxError;

        intAmount *= 10;
        intAmount += t - '0';
    }
    // debug output for the parser
    hwlib::cout << action << ' ' << amount << "\r\n";

    if (action.length() == 1) {
        if (action[0] == 'X') {
            robotArmController.rotateAxis(RobotAxis::X, intAmount, direction);
            return Status::Successful;
        }

        if (action[0] == 'Y') {
            robotArmController.rotateAxis(RobotAxis::Y, intAmount, direction);
            return Status::Successful;
        }

        if (action[0] == 'Z') {
            robotArmController.rotateAxis(RobotAxis::Z, intAmount, direction);
            return Status::Successful;
        }
    } else {

        if (equal(action,  "WAIT_S", 6)) {
            hwlib::wait_ms(intAmount * 1000);
            return Status::Successful;
        }

        if (equal(action, "WAIT_MS", 7)) {
            hwlib::wait_ms(intAmount);
            return Status::Successful;
        }

        if (equal(action, "RESET", 5)) {
            robotArmController.startup();
            return Status::Successful;
        }
    }

    return Status::SyntaxError;
}
