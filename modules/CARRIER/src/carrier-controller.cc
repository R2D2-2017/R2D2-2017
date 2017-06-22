/**
 * \file
 * \author    Remco Ruttenberg
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "carrier-controller.hh"

using namespace Carrier;

CarrierController::CarrierController(MotorController &motorController,
                                     SerialCom &serialCom,
                                     std::vector<HcSr04> &sonarSensors,
                                     int speed) :
                   motorController{ motorController }, serialCom{serialCom},
                   sonarSensors{ sonarSensors }, speed{ speed } {
    state = std::make_unique<IdleState>(*this);
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
            this->state = std::make_unique<ForwardState>(*this);
        break;

        case CarrierState::Backward:
            this->state = std::make_unique<BackwardState>(*this);
        break;

        case CarrierState::Clockwise:
            this->state = std::make_unique<ClockwiseState>(*this);
        break;

        case CarrierState::CounterClockwise:
            this->state = std::make_unique<CounterClockwiseState>(*this);
        break;

        case CarrierState::Idle:
            this->state = std::make_unique<IdleState>(*this);
        break;

        case CarrierState::Auto:
            this->state = std::make_unique<AutoState>(*this);
        break;

        case CarrierState ::Avoidance:
            this->state = std::make_unique<AvoidanceState>(*this);
        break;
    }
}

int CarrierController::getSpeed() {
    return speed;
}

void CarrierController::setSpeed(int speed) {
    this->speed = speed;
}

MotorController& CarrierController::getMotorController() {
    return motorController;
}

SerialCom& CarrierController::getSerialCom() {
    return serialCom;
}

std::vector<int> CarrierController::getSonarValue(SonarDirection direction) {
    if(direction == SonarDirection::All) {
        return std::vector<int>{sonarSensors[North].getDistance(),
                                sonarSensors[East].getDistance(),
                                sonarSensors[South].getDistance(),
                                sonarSensors[West].getDistance()};
    } else {
        return std::vector<int>{sonarSensors[direction].getDistance()};
    }
}