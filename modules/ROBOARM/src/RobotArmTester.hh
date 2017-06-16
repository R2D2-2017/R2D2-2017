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
    static const hwlib::string<12> commandList1[];
    static const hwlib::string<12> commandList2[];

    RoboArm::RobotArmController &robotarm;

    void run_test(const hwlib::string<12> *commandList, int commandListLen);

public:
    RobotArmTester(RoboArm::RobotArmController &robotarm);

    void run(int test = 0);
};


#endif //ROBOARM_ROBOTARMTESTER_HH
