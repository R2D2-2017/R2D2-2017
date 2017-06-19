/**
 * \file
 * \author    Remco Ruttenberg
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "carrier-controller.hh"
using namespace Carrier;

CarrierController::CarrierController(MotorController & motorController,
    HcSr04 & sonarSensor, int speed) :
    motorController{ motorController }, sonarSensor{  sonarSensor }, speed{ speed }
{
    state = new IdleState(this);
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
            this->state = new ForwardState(this);
        break;

        case CarrierState::Backward:
            this->state = new BackwardState(this);
        break;

        case CarrierState::Clockwise:
            this->state = new ClockwiseState(this);
        break;

        case CarrierState::CounterClockwise:
            this->state = new CounterClockwiseState(this);
        break;

        case CarrierState::Idle:
            this->state = new IdleState(this);
        break;
    }
}

int CarrierController::getSpeed() {
    return speed;
}

void CarrierController::setSpeed(int speed) {
    this->speed = speed;
}

MotorController* CarrierController::getMotorController() {
    return &motorController;
}

HcSr04* CarrierController::getSonar() {
    return &sonarSensor;
}