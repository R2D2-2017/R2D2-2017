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

    RoboArm::RobotArmController &robotarm;

    void test(hwlib::string<12> *commandList, int commandListLen);

public:
    RobotArmTester(RoboArm::RobotArmController &robotarm);

    void run(int test = 0);
};


#endif //ROBOARM_ROBOTARMTESTER_HH
