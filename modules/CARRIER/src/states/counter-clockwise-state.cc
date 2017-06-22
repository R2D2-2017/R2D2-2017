/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "counter-clockwise-state.hh"

using namespace Carrier;

CounterClockwiseState::CounterClockwiseState(CarrierController &controller /*, int degrees*, SlitSensor &object*/) : ICarrierState{ controller } {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller.getMotorController().left(controller.getSpeed());
    //template code for when the slitsensor does work
    // while(object.rotations() != degrees * (number of rotations per degree)){
    //  }
    // controller.getMotorController().stop();
}

void CounterClockwiseState::update() {

}

CarrierState CounterClockwiseState::getState() {
    return CarrierState::CounterClockwise;
}
