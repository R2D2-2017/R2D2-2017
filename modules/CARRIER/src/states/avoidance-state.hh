/**
 * \file
 * \author    Jip Galema
 * \author    Luke Roovers
 * \brief     Class to control the  autonomous state of the carrier
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once
#include "../carrier-controller.hh"
#include "i-carrier-state.hh"
namespace Carrier {

/**
 * \brief Forward declaration of the CarrierController class
 */
class CarrierController;

/**
 * \brief AvoidanceState class to control the avoidance state of the CarrierController class
 */
class AvoidanceState : public ICarrierState {
private:
    /// Threshold for the distance between the sensor and the object
    int threshold = 25;
public:
    /**
     * \brief Constructor for the AvoidanceState class
     * \param[in] controller Reference of a CarrierController that the AvoidanceState can use to control the carrier
     */
    AvoidanceState(CarrierController &controller);

    /**
     * \brief Updates the current state
     * Implementation of the virtual method from the interface.
     * Will be called in the CarrierController class to update
     * This update turns the carrier around (+/- 180 degrees)
     */
    void update();

    /**
    * \brief Returns the AvoidanceState enum from CarrierState
    */
    CarrierState getState();

};
}