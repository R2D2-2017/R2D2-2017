/**
 * \file
 * \brief     KY101 chip interface
 * \author    Luke Rovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

//\brief Simple boundary class for the KY101 chip
class Ky101 {
private:
    // hwlib pin_in that the chip is wired to
    hwlib::target::pin_in &signal;

public:
    // Constructor for the Ky101 classs
    //\param signal hwlib::pin_in to read the input from
    Ky101(hwlib::target::pin_in &signal);

    // Function that returns if input is high or low
    //\return bool digital input of pin
    bool get();
};
