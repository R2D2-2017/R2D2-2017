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

/**
 * \brief Forward declaration of the CarrierController class
 */
class CarrierController;

/**
 * \brief ClockwiseState class to control the ClockwiseState in the CarrierController
 */
class ClockwiseState : public ICarrierState {
    private:
        /// Reference of the CarrierController so it can be used in the states
        CarrierController* controller;
    public:
        /**
         * \brief Constructor for the ClockwiseState class
         * \param[in] controller Reference of a CarrierController that the ClockwiseState can use to controll the carrier
         */
        ClockwiseState(CarrierController* controller);

        /**
         * \brief Updates the current state
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update
         */
        void update();
        /**
         * \brief Returns the ClockwiseState enum from CarrierState
         */
        CarrierState getState();
};

}
