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

namespace RoboArm {
    namespace Parser {
        enum class Status {
            Successful,
            SyntaxError,
        };

        /**
         * \brief Check if string is equal to command
         *
         * \param[in]  String to compare
         * \param[in]  String to compare
         * \param[in]  Length of string
         *
         * \return returns true if equal
         */
        bool equal(const hwlib::string<0> &l, const char *r, unsigned int len);

        /**
         * \brief Parses a string and drives the servo motor
         *
         * \param[in]  command   how the servo should be moving as a string eg: "x 42"
         * \param[in]  RobotArmController  RobotArmController class that parser can executes commands for
         *
         * \return returns an status code so you can check if the execution was done successfully
         */
        Status parseCommand(const hwlib::string<0> &command, RobotArmController &robotArm);
    }
}
