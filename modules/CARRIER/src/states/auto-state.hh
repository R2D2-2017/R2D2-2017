/**
 * \file
 * \author    Jip Galema
 * \brief     Class to control the  autonomous state of the carrier
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once
#include "i-carrier-state.hh"
#include "../carrier-controller.hh"
#include <stdlib.h>
#include <time.h>

namespace Carrier{


/**
 * \brief Forward declaration of the CarrierController class
 * */
class CarrierController;


/**
 * \brief AutoState class to control the autonomous state of the CarrierController
 * */
class AutoState : public ICarrierState{
    public:

         /**
        * \brief Constructor for the AutoState class
        * \param[in]controller Reference of a CarrierController that the AutoState can use to control the carrier
        * */
        AutoState(CarrierController &controller);

        /**
         * \brief Updates the current state
         * Implementation of the virtual method from the interface.
         * Will be called in the CarrierController class to update
         * This update method chooses an random number and follows the
         * instruction corresponding to the index from the states array then
         * adds an delay depending on the instruction this happens 20 times
         */
        void update();
        /**
        * \brief Returns the AutoState enum from CarrierState
        */
        CarrierState getState();
    private:
        /// Array of available states
        CarrierState states[] = {Carrier::CarrierState::Idle, Carrier::CarrierState::Forward,
                               Carrier::CarrierState::Backward, Carrier::CarrierState::Clockwise,
                               Carrier::CarrierState::CounterClockwise};
    };





}