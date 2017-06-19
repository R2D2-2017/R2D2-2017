/**
 * \file
 * \author    Jan Halsema, David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "parser.hh"

using namespace RoboArm::Parser;

Status RoboArm::Parser::parseCommand(const hwlib::string<0> &command,
                                     RobotArmController &robotArmController,
                                     I2C &i2c) {
    size_t space = 0; // the place of the space

    // find space
    for (; space < command.length() - 1 && command[space] != ' '; space++);
    if (space == command.length() - 1) {
        if (command == "RESET") {
            robotArmController.startup();
            return Status::Successful;
        }
        if (command == "EN") {
            robotArmController.enable();
            return Status::Successful;
        }
        if (command == "DIS") {
            robotArmController.disable();
            return Status::Successful;
        }
        if (command == "I2CDemo") {
            i2c.runDemo();
            return Status::Successful;
        }
    } else {
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

        if (action == "M1") {
            robotArmController.rotateMotor(Motor::M1, intAmount, direction);
            return Status::Successful;
        }
        if (action == "M2") {
            robotArmController.rotateMotor(Motor::M2, intAmount, direction);
            return Status::Successful;
        }
        if (action == "M3") {
            robotArmController.rotateMotor(Motor::M3, intAmount, direction);
            return Status::Successful;
        }
        if (action == "WAIT_S") {
            hwlib::wait_ms(intAmount * 1000);
            return Status::Successful;
        }
        if (action == "WAIT_MS") {
            hwlib::wait_ms(intAmount);
            return Status::Successful;
        }
    }

    return Status::SyntaxError;
}
