/**
 * \file
 * \author    Remco Ruttenberg
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "carrier-controller.hh"
using namespace Carrier;

CarrierController::CarrierController(std::shared_ptr<MotorController> motorController,
    std::shared_ptr<HcSr04> sonarSensor, int speed) :
    motorController{ motorController }, sonarSensor{ sonarSensor }, speed{ speed }
{
    state = std::make_unique<IdleState>(this);
}

CarrierState CarrierController::currentState() {
    return state->getState();
}

void CarrierController::update() {
   state->update();
}

void CarrierController::setState(CarrierState state) {
    switch(state) {
        case CarrierState::Forward:
            this->state = std::make_unique<ForwardState>(this);
        break;

        case CarrierState::Backward:
            this->state = std::make_unique<BackwardState>(this);
        break;

        case CarrierState::Clockwise:
            this->state = std::make_unique<ClockwiseState>(this);
        break;

        case CarrierState::CounterClockwise:
            this->state = std::make_unique<CounterClockwiseState>(this);
        break;
        case CarrierState::Idle:
            this->state = std::make_unique<IdleState>(this);
        break;
    }
}

int CarrierController::getSpeed() {
    return speed;
}

void CarrierController::setSpeed(int speed) {
    this->speed = speed;
}

std::shared_ptr<MotorController> CarrierController::getMotorController() {
    return motorController;
}

std::shared_ptr<HcSr04> CarrierController::getSonar() {
    return sonarSensor;
}