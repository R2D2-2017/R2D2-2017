/**
 * \file
 * \brief     Robot arm controller
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "ky101.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"

const int microStepsArms = 8;
const int microStepsBase = 16;
const int smallBaseGear  = 20;
const int smallArmGear   = 11;
const float stepSize     = 1.65;

const int bigGear = 45;
const float baseStepRatio = bigGear / smallBaseGear;
const float armStepRatio  = bigGear / smallArmGear;

// Enum class for the different axes on the robot arm
enum class RobotAxis : uint8_t { X, Y, Z };

// Enum class for the different limit switches
enum class RobotLimitSwitch : uint8_t { BOTH, X, Y, NONE };

//\brief Robot Arm Controller to control 3 different stepper motors
class RobotArmController {
private:
    // The different stepper motors you can use
    Stepper               &xAxis, &yAxis, &zAxis;
    hwlib::target::pin_in &xLimitSwitch;
    hwlib::target::pin_in &yLimitSwitch;
    Ky101                  ky101;

public:
    // Constructor for the Robot arm controller
    //\param[in]  xAxis  stepper motor that is used as the x axis
    //\param[in]  yAxis  stepper motor that is used as the y axis
    //\param[in]  zAxis  stepper motor that is used as the z axis
    RobotArmController(Stepper &xAxis, Stepper &yAxis, Stepper &zAxis,
                       hwlib::target::pin_in &xLimitSwitch, hwlib::target::pin_in &yLimitSwitch,
                       Ky101 &ky101);

    // Rotate the given axis to the set amount of degrees (clockwise or
    // counterclockwise)
    //\param[in]  axis      The axis you want to rotate on
    //\param[in]  degrees   how many degrees you want to rotate
    //\param[in]  clockwise the direction the axis will rotate
    void rotateAxis(RobotAxis axis, int degrees, bool clockwise);

    // Set up the robot at its starting position
    void startup();

    // Function check if the robot has reached it's limitations
    //\return enum based on which switch is pressed
    RobotLimitSwitch checkLimitations();
};
