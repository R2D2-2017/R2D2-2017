/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "backward-state.hh"

using namespace Carrier;

BackwardState::BackwardState(CarrierController &controller) : ICarrierState{ controller } {
    if (controller.getSonarValue(SonarDirections::South)[0] <= 50) {
        controller.setState(CarrierState::Idle);
    } else {
        controller.getMotorController().backward(controller.getSpeed());
    }
}

void BackwardState::update() {
    if (controller.getSonarValue(SonarDirections::South)[0] <= 50) {
        controller.setState(CarrierState::Idle);
    }
}

CarrierState BackwardState::getState() {
    return CarrierState::Backward;
}
