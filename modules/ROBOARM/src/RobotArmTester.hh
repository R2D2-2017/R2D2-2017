//
// Created by david on 14-6-17.
//

#ifndef ROBOARM_ROBOTARMTESTER_HH
#define ROBOARM_ROBOTARMTESTER_HH

#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"

class RobotArmTester {
    static const char *commandList1[15];
    static const char *commandList2[26];

    RoboArm::RobotArmController &robotarm;

    void run_test(const char *commandList[], int commandListLen);

public:
    RobotArmTester(RoboArm::RobotArmController &robotarm);

    void run(int test = 0);
};


#endif //ROBOARM_ROBOTARMTESTER_HH
