/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "counter-clockwise-state.hh"

using namespace Carrier;

CounterClockwiseState::CounterClockwiseState(CarrierController &controller) : ICarrierState{ controller } {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller.getMotorController().left(controller.getSpeed());
}

void CounterClockwiseState::update() {

}

CarrierState CounterClockwiseState::getState() {
    return CarrierState::CounterClockwise;
}
