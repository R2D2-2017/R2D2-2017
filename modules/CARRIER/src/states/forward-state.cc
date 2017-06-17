/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "forward-state.hh"
using namespace Carrier;

ForwardState::ForwardState(CarrierController* controller) : controller(controller) {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller->getMotorController()->forward(100);
}

void ForwardState::update() {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
}

CarrierState ForwardState::getState() {
    return CarrierState::Forward;
}
