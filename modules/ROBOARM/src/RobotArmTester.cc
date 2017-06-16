/**
 * \file
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "RobotArmTester.hh"

void RobotArmTester::test(hwlib::string<12> *commandList, int commandListLen){
    using namespace RoboArm::Parser;

    for (int i = 0; i < commandListLen; ++i) {
        Status result = parseCommand(commandList[i], robotarm);

        switch (result) {
            case Status::SyntaxError:
                hwlib::cout << "Syntax error" << "\r\n";
                break;
            case Status::Successful:
                break;
        }
    }
}

RobotArmTester::RobotArmTester(RoboArm::RobotArmController &robotarm) :
        robotarm(robotarm) {}

void RobotArmTester::run(int test) {

    hwlib::cout << "START SEQUENCE" << "\r\n";
    robotarm.enable();

    robotarm.startup(); // resets the robot position
    hwlib::cout << "Position has been reset" << "\r\n";

    if (test == 0 || test == 1) {
        hwlib::cout << "Run test 1" << "\r\n";
        test(commandList1, sizeof(commandList1)/ sizeof(commandList1[0]));
    }

    if (test == 0 || test == 2) {
        hwlib::cout << "Run test 2" << "\r\n";
        test(commandList2, sizeof(commandList2)/ sizeof(commandList2[0]));
    }

    robotarm.disable();
    hwlib::cout << "END SEQUENCE" << "\r\n";
}