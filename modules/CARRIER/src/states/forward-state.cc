/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "forward-state.hh"
using namespace Carrier;

ForwardState::ForwardState(CarrierController* controller) : controller(controller) {
    if (controller->getSonar()->getDistance() <= 50) {
        controller->setState(CarrierState::Idle);
    } else {
        controller->getMotorController()->forward(controller->getSpeed());
    }
}

void ForwardState::update() {
    if (controller->getSonar()->getDistance() <= 50) {
        controller->setState(CarrierState::Idle);
    }
}

CarrierState ForwardState::getState() {
    return CarrierState::Forward;
}
