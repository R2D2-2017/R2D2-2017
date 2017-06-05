/**
 * \file
 * \brief     Stepper motor interface (dvr8225)
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

/// brief Simple interface to control a stepper motor
class Stepper {
private:
    /// Pin that is used for the clockwise or counterclockwise direction
    hwlib::target::pin_out &dir_pin;
    /// Pin that is used to control the step of the stepper motor
    hwlib::target::pin_out &stp_pin;

public:
    /**
     *\brief Constructor for the stepper motor
     *\param[in] dir_pin pin is used for the clockwise or counterclockwise direction
     *\param[in] stp_pin pin is used to control the step of the stepper motor
     */
    Stepper(hwlib::target::pin_out &dir_pin, hwlib::target::pin_out &stp_pin);

    /**
     *\brief Let the motor step a certain amount of steps
     *\param[in] amount the amount of steps to be taken
     *\param[in] clockwise the direction the motor will rotate to
     */
    void step(bool clockwise);
};
