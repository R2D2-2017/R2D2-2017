/**
 * \file
 * \brief     Command Parser
 * \author    Jan Halsema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "wrap-hwlib.hh"
#include "robot-arm.hh"
#include "robot-arm-tester.hh"
#include "i2c.hh"

namespace RoboArm {
    namespace Parser {
        enum class Status {
            Successful,
            SyntaxError,
        };

        /**
         * \brief Get int from string
         *
         * \param[in] hwlib::string String to get int from
         *
         * \return returns the int from the string
         */
        int stringToInt(const hwlib::string<0> &string);

        /**
         * \brief Parses a string and drives the servo motor
         *
         * \param[in]  command   how the servo should be moving as a string eg: "x 42"
         * \param[in]  RobotArmController  RobotArmController class that the parser can executes commands for
         * \param[in]  I2C  I2C class that the parser can executes commands for
         *
         * \return returns an status code so you can check if the execution was done successfully
         */
        Status parseCommand(const hwlib::string<0> &command,
                            RobotArmController &robotArm,
                            I2C &i2ck);
    }
}
