/**
 * \file
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "robotarmtester.hh"

robotarmtester::robotarmtester(RoboArm::RobotArmController &robotarm) :
        robotarm(robotarm) {}

void robotarmtester::run(int test) {
// TODO parser requires this hwlib fix - https://github.com/wovo/hwlib/pull/6
    hwlib::string<12> commandList1[] = {
            // Reset
            "RESET 1",

            // Z axis test
            "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2",

            // Y axis test
            "Y 90", "WAIT_S 2", "Y -45", "WAIT_S 2",

            // X axis test
            "X 45", "WAIT_S 2", "X -45", "WAIT_S 2",

            // Reset
            "RESET 1",
    };

    hwlib::string<12> commandList2[] = {
            // Reset
            "RESET 1",

            // Z axis test
            "WAIT_S 2", "Z 90", "WAIT_S 2", "Z -90", "WAIT_S 2", "Z 180",
            "WAIT_S 2", "Z -180", "WAIT_S 2",

            // Y axis test
            "Y 90", "WAIT_S 2", "Y -90", "WAIT_S 2", "Y 180", "WAIT_S 2",
            "Y -180", "WAIT_S 2",

            // X axis test
            "X 90", "WAIT_S 2", "X -90", "WAIT_S 2", "X 180", "WAIT_S 2",
            "X -240",

            // Reset
            "RESET 1",
    };

    hwlib::cout << "START SEQUENCE" << "\r\n";
    robotarm.enable();

    robotarm.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << "\r\n";

    using namespace RoboArm::Parser;

    if (test == 0 || test == 1) {
        hwlib::cout << "Run test 1" << "\r\n";
        for (const auto &command : commandList1) {
            Status result = parseCommand(command, robotarm);

            switch (result) {
                case Status::SyntaxError:
                    hwlib::cout << "Syntax error" << "\r\n";
                    break;
                case Status::Successful:
                    break;
            }
        }
    }

    if (test == 0 || test == 2) {
        hwlib::cout << "Run test 2" << "\r\n";
        for (const auto &command : commandList2) {
            Status result = parseCommand(command, robotarm);

            switch (result) {
                case Status::SyntaxError:
                    hwlib::cout << "Syntax error" << "\r\n";
                    break;
                case Status::Successful:
                    break;
            }
        }
    }

    robotarm.disable();
    hwlib::cout << "END SEQUENCE" << "\r\n";
}