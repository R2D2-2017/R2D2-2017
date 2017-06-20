/**
 * \file
 * \author    Bob Thomas
 * \brief     Interface for the state classes
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

namespace Carrier
{

/**
 * \brief The different states the carrier can be in.
 * 
 * To add a new state update the CarrierState enum and create a new state class
 * Use the ForwardState class as an example
 */
enum class CarrierState {
    Idle,
    Forward,
    Backward,
    Clockwise,
    CounterClockwise,
    Auto,
    Avoidance
};

// Forward declaration of the CarrierController class
class CarrierController;

/**
 * \brief Interface for the carrier states
 * 
 * This interface is used in all the state classes for the carrier state.
 * It makes sure every state has an update and every state has the ability to return it's own state
 */
class ICarrierState {
    protected:
        /// Reference of the CarrierController so it can be used in the states
        CarrierController &controller;
    public:
        /**
         * \brief Constructor for ICarrierState
         *
         * NOTE: Cannot be instantiated by itself, only derived classes can.
         *
         * \param[in] controller Reference of the CarrierController that derived classes (states) can use to control the carrier
         */
        ICarrierState(CarrierController & controller) : controller{ controller }
        {}

        /**
         * \brief Virtual method that can be called in every subclass to update the state
         */
        virtual void update() = 0;

        /**
         * \brief Virtual method that can be called in every subclass to return the state
         */
        virtual CarrierState getState() = 0;
};
}
