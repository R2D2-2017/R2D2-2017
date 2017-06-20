/**
 * \file
 * \author    Jan Halsema, David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "parser.hh"

using namespace RoboArm::Parser;

int stringToInt(const hwlib::string<0> &amount) {
    int intAmount = 0;
    // string to int routine because no stdlib and not present in hwlib :(
    for (size_t i = 0; i < amount.length(); i++) {
        char t = amount[i];

        if (!i) { // only do this the first time
            if (t == '-') {
                continue;
            }
        }
        // no number no parsing
        if (!(t >= '0' && t <= '9')) return -1;

        intAmount *= 10;
        intAmount += t - '0';
    }
    return intAmount;
}

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
        if (command == "OPEN") {
            //1 is the is the servo number
            //175 is the degrease for the servo to fully open
            i2c.moveServoTo(1, 175);
            return Status::Successful;
        }
        if (command == "CLOSE") {
            //1 is the is the servo number
            //92 is the degrease for the servo to fully close
            i2c.moveServoTo(1, 92);
            return Status::Successful;
        }
    } else {
        hwlib::cout << command << "\r\n";
        const auto start = command.begin();
        const auto end = command.end();
        const hwlib::string<8> action = command.range(start, start + space);
        const hwlib::string<16> amount = command.range(start + space + 1, end);

        if (action == "MOVETO") {
            for (space = 0;
                 space < amount.length() - 1 && amount[space] != ' ';
                 space++);
            const auto startx = amount.begin();
            const auto endx = amount.end();
            float x = stringToInt(amount.range(startx, startx + space));
            const hwlib::string<16> amount2 = command.range(startx + space + 1, endx);

            for (space = 0;
                 space < amount2.length() - 1 && amount2[space] != ' ';
                 space++);
            const auto starty = amount2.begin();
            const auto endy = amount2.end();
            float y = stringToInt(amount2.range(starty, starty + space));
            float z = stringToInt(amount2.range(starty + space + 1, endy));
            if (x < 0 || y < 0 || z < 0) {
                return Status::SyntaxError;
            }
            robotArmController.moveTo({x, y, z});
            return Status::Successful;
        } else {
            // true if we go counterclockwise (negative value)
            bool direction = amount[0] == '-';
            int16_t intAmount = (int16_t) stringToInt(amount);
            if (intAmount < 0) {
                return Status::SyntaxError;
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
    }

    return Status::SyntaxError;
}
