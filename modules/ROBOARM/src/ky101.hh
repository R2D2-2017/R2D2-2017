/**
 * \file
 * \brief     KY101 chip interface
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

/**
 * \brief Simple boundary class for the KY101 chip
*/
class Ky101 {
private:
    /// hwlib pin_in that the chip is wired to
    hwlib::target::pin_in &signal;

public:
    /**
     * \brief Constructor for the Ky101 class
     *
     * \param[in]    signal  pin to read input from
    */
    Ky101(hwlib::target::pin_in &signal);

    /**
     * \brief Function that returns if input is high or low
     *
     * \return bool digital input of pin
     */
    bool get();
};
