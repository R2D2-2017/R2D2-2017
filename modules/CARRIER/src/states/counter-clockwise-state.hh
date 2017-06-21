/**
 * \file
 * \author    Bob Thomas
 * \brief     Class to control the backward state of the carrier
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "i-carrier-state.hh"
#include "../carrier-controller.hh"

namespace Carrier {

// Forward declaration of the CarrierController class
class CarrierController;

/**
 * \brief ClockwiseState class to control the CounterClockwiseState in the CarrierController
 */
class CounterClockwiseState : public ICarrierState {
    public:
        /**
         * \brief Constructor for the CounterClockwiseState class
         * 
         * \param[in] controller Reference of the CarrierController that the CounterClockwiseState can use to control the carrier
         */
        CounterClockwiseState(CarrierController &controller);

        /**
         * \brief Perform (update) actions based on the current state.
         *
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update.
         */
        void update();

        /**
         * \brief Returns the CounterClockwiseState enum from CarrierState
         */
        CarrierState getState();
};

}