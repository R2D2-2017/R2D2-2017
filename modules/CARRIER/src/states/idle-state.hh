/**
 * \file
 * \author    Bob Thomas
 * \brief     Class to control the idle state of the carrier
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
 * \brief Defines actions for the Idle state
 */
class IdleState : public ICarrierState {
    public:
        /**
         * \brief Constructor for the IdleState class
         * 
         * \param[in]  controller  reference of the CarrierController that the
         * IdleState can use to control the carrier
         */
        IdleState(CarrierController &controller);

        /**
         * \brief Perform (update) actions based on the current state.
         *
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update.
         */
        void update();

        /**
         * \brief Returns the IdleState enum from CarrierState
         */
        CarrierState getState();
};

}
