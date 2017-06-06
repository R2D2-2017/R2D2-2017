/**
 * \file
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "ky101.hh"

Ky101::Ky101(hwlib::target::pin_in &signal) : signal(signal) {}

bool Ky101::get() {
    return signal.get();
}
