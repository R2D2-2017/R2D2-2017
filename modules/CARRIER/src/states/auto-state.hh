/**
 * \file
 * \author    Jip Galema
 * \brief     Class to control the autonomous state of the carrier
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "i-carrier-state.hh"
#include "../carrier-controller.hh"
#include <array>

namespace Carrier{

// Forward declaration of the CarrierController class
class CarrierController;

/**
 * \brief Defines actions for the autonomous state
 */
class AutoState : public ICarrierState {
private:
    /// Array of available states
    const std::array<CarrierState, 5> states{
            {CarrierState::Idle,
                    CarrierState::Forward,
                    CarrierState::Backward,
                    CarrierState::Clockwise,
                    CarrierState::CounterClockwise}};

    int threshold = 25;

public:
    /**
     * \brief Constructor for the AutoState class
     *
     * \param[in]  controller  reference of the CarrierController that the
     * AutoState can use to control the carrier
     */
    AutoState(CarrierController &controller);

    /**
     * \brief Updates the current state
     *
     * Implementation of the virtual method from the interface.
     * Will be called in the CarrierController class to update.
     * This update method chooses a random number and follows the
     * instruction corresponding to the index from the states array, then
     * adds a delay depending on the instruction (this happens 20 times)
     */
    void update();

    /**
     * \brief Returns the Auto state
     */
    CarrierState getState();

    };
}