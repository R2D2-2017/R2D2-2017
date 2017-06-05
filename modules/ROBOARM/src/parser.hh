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

enum class Status : uint8_t {
    Succesful = 0,
    SyntaxError,
    Limit,
};

/**
 * \brief Parses a string and drives the servo motor
 *
 * \param[in]  command   how the servo should be moving as a string eg: "x 42"
 * \param[in]  executor  an interface that provides ways of moving a servo, or anything for that matter
 *
 * \return               returns an error code so you can check if the execution was done successfully
 */
Status parseCommand(const hwlib::string<0> &command, RobotArmController &robotArm);
