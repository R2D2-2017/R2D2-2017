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

namespace RoboArm {

/// Enum class for the different axes on the robot arm
    enum class RobotAxis {
        X, Y, Z
    };

/// Enum class for the different limit switches
    enum class RobotLimitSwitch {
        BOTH, X, Y, NONE
    };

/// Robot Arm Controller to control 3 different stepper motors
    class RobotArmController {
    private:
        /// microSteps the driver board is using to control the X and Y axes
        static constexpr int microStepsArms = 8;
        /// microSteps the driver board is using to control the Z axis
        static constexpr int microStepsBase = 16;
        /// How many teeth the driver gear has on the Z axis
        static constexpr int smallBaseGear = 20;
        /// How many teeth the driver gear for the arms have for the X and Y axes
        static constexpr int smallArmGear = 11;
        /// How many teeth the driven gear has for all three axes
        static constexpr int bigGear = 45;
        /// The size of a step to turn the motor 1 degree
        static constexpr float stepSize = 1.65;
        /// Calculating the ratio to drive a gear correctly - http://www.wikihow.com/Determine-Gear-Ratio
        static constexpr float baseStepRatio = bigGear / smallBaseGear;
        /// Calculating the ratio to drive a gear correctly - http://www.wikihow.com/Determine-Gear-Ratio
        static constexpr float armStepRatio = bigGear / smallArmGear;

        /// The different stepper motors you can use
        Stepper &xAxis, &yAxis, &zAxis;
        /// Input pins on which the X limit switch get wired to check limitation status
        hwlib::target::pin_in &xLimitSwitch;
        /// Input pins on which the Y limit switch get wired to check limitation status
        hwlib::target::pin_in &yLimitSwitch;
        /// Class that reads input to see if the base is on it's starting position for the Z axis
        Ky101 ky101;

    public:
        /**
         *\brief Constructor for the Robot arm controller
         *\param[in]  xAxis  stepper motor that is used as the x axis
         *\param[in]  yAxis  stepper motor that is used as the y axis
         *\param[in]  zAxis  stepper motor that is used as the z axis
         *\param[in]  xLimitSwitch  pin on which the limit switch for the X axis is wired
         *\param[in]  yLimitSwitch  pin on which the limit switch for the Y axis is wired
         *\param[in]  ky101 class that's used to determine the start position for the Z axis
         */
        RobotArmController(Stepper &xAxis, Stepper &yAxis, Stepper &zAxis,
                           hwlib::target::pin_in &xLimitSwitch, hwlib::target::pin_in &yLimitSwitch,
                           Ky101 &ky101);

        /**
         *\brief Rotate the given axis to the set amount of degrees (clockwise or counterclockwise)
         *\param[in]  axis      The axis you want to rotate on
         *\param[in]  degrees   how many degrees you want to rotate
         *\param[in]  clockwise the direction the axis will rotate
         */
        void rotateAxis(RobotAxis axis, int degrees, bool clockwise);

        /// Set up the robot at its starting position
        void startup();

        /**
         *\brief Function check if the robot has reached it's limitations
         *\return enum based on which switch is pressed
         */
        RobotLimitSwitch checkLimitations();
    };
}
