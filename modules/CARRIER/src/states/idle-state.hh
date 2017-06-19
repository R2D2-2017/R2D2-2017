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

/**
 * \brief Forward declaration of the CarrierController class
 */
class CarrierController;

/**
 * \brief IdleState class to control the IdleState in the CarrierController
 */
class IdleState : public ICarrierState {
    public:
        /**
         * \brief Constructor for the IdleState class
         * \param[in] controller Reference of a CarrierController that the IdleState can use to controll the carrier
         */
        IdleState(CarrierController &controller);

        /**
         * \brief Updates the current state
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update
         */
        void update();

        /**
         * \brief Returns the IdleState enum from CarrierState
         */
        CarrierState getState();
};

}
