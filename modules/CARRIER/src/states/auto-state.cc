/**
 * \file
 * \author    Jip Galema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "auto-state.hh"

using namespace Carrier;

AutoState::AutoState(CarrierController &controller) : ICarrierState{ controller } {
    controller.getMotorController().forward(controller.getSpeed());
}

void AutoState::update() {
    std::srand(std::time(0)); // Use the current time as a seed for the random generator
    CarrierState next_state;
    for(int i = 0; i < 20; i++) {
        next_state = states[std::rand() % 5]; // Pick a state at random
        if (next_state == CarrierState::CounterClockwise) {
            controller.getMotorController().left(controller.getSpeed());
            delay(250);
        } else if (next_state == CarrierState::Clockwise) {
            controller.getMotorController().right(controller.getSpeed());
            delay(250);
        } else if (next_state == CarrierState::Forward) {
            if (controller.getSonarValue(SonarDirection::North)[0] <= threshold) {
                controller.getMotorController().stop();
                controller.getSerialCom().write("PATH OBSTRUCTED CANT GO FORWARDS");
                controller.setState(CarrierState::Avoidance);
            } else {
                controller.getMotorController().forward(controller.getSpeed());
            }
            delay(500);
        } else if (next_state == CarrierState::Backward) {
            if (controller.getSonarValue(SonarDirection::South)[0] <= threshold) {
                controller.getMotorController().stop();
                controller.getSerialCom().write("PATH OBSTRUCTED! CANNOT GO BACKWARDS");
            } else {
                controller.getMotorController().forward(controller.getSpeed());
            }
            delay(500);
        } else if (next_state == CarrierState::Idle) {
            controller.getMotorController().stop();
            delay(100);
        }
    }
    controller.getMotorController().stop();
}

CarrierState AutoState::getState() {
    return CarrierState::Auto;
}
