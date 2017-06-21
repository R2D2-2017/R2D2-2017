/**
 * \file
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "robot-arm-tester.hh"

const char *RobotArmTester::commandList1[15] = {
        // Reset
        "RESET",

        // M3 aM2is test
        "WAIT_S 2", "M3 -90", "WAIT_S 2", "M3 90", "WAIT_S 2",

        // M1 aM2is test
        "M1 -90", "WAIT_S 2", "M1 45", "WAIT_S 2",

        // M2 aM2is test
        "M2 -45", "WAIT_S 2", "M2 45", "WAIT_S 2",

        // Reset
        "RESET",
};

const char *RobotArmTester::commandList2[13] = {
        // Reset
        "RESET",

        "MOVETO 20 15 0",
        "MOVETO 10 10 90",
        "MOVETO 20 0 90",
        "OPEN",
        "MOVETO 30 0 90",
        "WAIT_S 2",
        "CLOSE",
        "WAIT_S 1",
        "MOVETO 20 10 0",
        "WAIT_S 3",
        "OPEN",

        // Reset
        "RESET",
};

void RobotArmTester::run_test(const char *commandList[], int commandListLen){
    using namespace RoboArm::Parser;

    for (int i = 0; i < commandListLen; ++i) {
        Status result = parseCommand((hwlib::string<12>)commandList[i], robotarm, i2c);

        switch (result) {
            case Status::SyntaxError:
                hwlib::cout << "Syntax error" << "\r\n";
                break;
            case Status::Successful:
                break;
        }
    }
}

RobotArmTester::RobotArmTester(RoboArm::RobotArmController &robotarm, I2C &i2c)
        : robotarm(robotarm), i2c(i2c) {}

void RobotArmTester::run(int test) {
    hwlib::cout << "START SEQUENCE" << "\r\n";
    robotarm.enable();

    robotarm.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << "\r\n";

    if (test == 0 || test == 1) {
        hwlib::cout << "Run test 1" << "\r\n";
        run_test(commandList1, sizeof(commandList1) / sizeof(commandList1[0]));
    }

    if (test == 0 || test == 2) {
        hwlib::cout << "Run test 2" << "\r\n";
        run_test(commandList2, sizeof(commandList2) / sizeof(commandList2[0]));
    }

    robotarm.disable();
    hwlib::cout << "END SEQUENCE" << "\r\n";
}