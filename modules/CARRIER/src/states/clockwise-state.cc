/**
 * \file
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "clockwise-state.hh"

using namespace Carrier;

ClockwiseState::ClockwiseState(CarrierController &controller /*, int degrees*, SlitSensor &object*/) : ICarrierState{ controller } {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }

     controller.getMotorController().right(controller.getSpeed());
    //template code for when the slitsensor does work
    // while(object.rotations() != degrees * (number of rotations per degree)){
    //  }
    // controller.getMotorController().stop();
}

void ClockwiseState::update() {

}

CarrierState ClockwiseState::getState() {
    return CarrierState::Clockwise;
}
