/**
* \file
* \author    Bob Thomas
* \copyright Copyright (c) 2017, The R2D2 Team
* \license   See LICENSE
*/

#include "idle-state.hh"

using namespace Carrier;

IdleState::IdleState(CarrierController &controller) : ICarrierState{ controller } {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller.getMotorController().stop();
}

void IdleState::update() {

}

CarrierState IdleState::getState() {
    return CarrierState::Idle;
}
