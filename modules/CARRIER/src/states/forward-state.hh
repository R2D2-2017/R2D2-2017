/**
 * \file
 * \author    Bob Thomas
 * \brief     Class to control the forward state of the carrier
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "../carrier-controller.hh"
#include "i-carrier-state.hh"

namespace Carrier {

// Forward declaration of the CarrierController class
class CarrierController;

/**
 * \brief Defines actions for the Forward state
 */
class ForwardState : public ICarrierState {
    public:
        /**
         * \brief Constructor for the ForwardState class
         * 
         * \param[in]  controller  reference of the CarrierController that the
         * ForwardState can use to control the carrier
         */
        ForwardState(CarrierController &controller);

        /**
         * \brief Perform (update) actions based on the current state.
         *
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update.
         */
        void update();

        /**
         * \brief Returns the ForwardState enum from CarrierState
         */
        CarrierState getState();
};

}
