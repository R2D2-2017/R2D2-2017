/**
 * \file
 * \brief     Robot arm controller
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"
#include "stepper.hh"
#include "KY101.hh"

const float stepSize = 1.65;
const int microStepsArms = 8;
const int microStepsBase = 16;
const int smallBaseGear = 20;
const int smallArmGear = 11;

const int bigGear = 45;
const float baseStepRatio = bigGear/smallBaseGear;
const float armStepRatio = bigGear/smallArmGear;


//Enum class for the different axes on the robot arm
enum class RobotAxis : uint8_t {
    X, Y, Z
};

//\brief Robot Arm Controller to control 3 different stepper motors
class RobotArmController {
private:
    // The different stepper motors you can use
    Stepper &x_axis, y_axis, z_axis;
    hwlib::target::pin_in & xLimitSwitch;
    hwlib::target::pin_in & yLimitSwitch;
    KY101 ky101;

public:
    //Constructor for the Robot arm controller
    //\param  x_axis stepper motor that is used as the x axis
    //\param  y_axis stepper motor that is used as the y axis
    //\param  z_axis stepper motor that is used as the z axis

    RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis, hwlib::target::pin_in & xLimitSwitch, hwlib::target::pin_in & yLimitSwitch, KY101 & ky101);

    // reset sequence to move towards the configured start position
    void reset();

    // Rotate the given axis to the set amount of degrees (clockwise or counterclockwise)
    //\param axis The axis you want to rotate on
    //\param degrees how many degrees you want to rotate
    //\param clockwise the direction the axis will rotate
    void rotateAxis(RobotAxis axis, int degrees, bool clockwise);

    // Set up the robot at its starting positions
    void startup();

    // Function check if the robot has reached it's limitations
    int checkLimitations();

};
