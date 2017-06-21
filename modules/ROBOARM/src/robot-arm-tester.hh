/**
 * \file
 * \author    David Driessen
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "ky101.hh"
#include "parser.hh"
#include "robot-arm.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"
#include "i2c.hh"

/**
 * \brief The test class to test functionality of the roboarm and run a test program
 */
class RobotArmTester {
    static const char *commandList1[15];
    static const char *commandList2[13];

    RoboArm::RobotArmController &robotarm;
    I2C &i2c;

    /**
     * \brief Runs a list of commands as test
     * \param commandList The list of commands to be run
     * \param commandListLen The length of the array of commands to be run
     */
    void run_test(const char *commandList[], int commandListLen);

public:
    /**
     * \param robotarm The robotarm to run the tests with
     * \param i2c The i2c bus the gripper is connected to
     */
    RobotArmTester(RoboArm::RobotArmController &robotarm, I2C &i2c);

    /**
     * \brief Runs a test on the robotarm
     * \param test The number of the test to run
     */
    void run(int test = 0);
};
