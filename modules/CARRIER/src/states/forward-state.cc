/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "forward-state.hh"

using namespace Carrier;

ForwardState::ForwardState(CarrierController &controller) : ICarrierState{ controller } {
    if (controller.getSonarValue(SonarDirections::North)[0] <= 50) {
        controller.setState(CarrierState::Idle);
        controller.getSerialCom().write("PATH OBSTRUCTED CANT GO FORWARD");
    } else {
        controller.getMotorController().forward(controller.getSpeed());
    }
}

void ForwardState::update() {
    if (controller.getSonarValue(SonarDirections::North)[0] <= 50) {
        controller.setState(CarrierState::Idle);
        controller.getSerialCom().write("PATH OBSTRUCTED CANT GO FORWARD");
    }
}

CarrierState ForwardState::getState() {
    return CarrierState::Forward;
}
