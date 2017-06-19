#include "backward-state.hh"
using namespace Carrier;

ClockwiseState::ClockwiseState(CarrierController* controller) {
    this->controller = controller;
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller->getMotorController()->right(controller->getSpeed());
}

void ClockwiseState::update() {

}

CarrierState ClockwiseState::getState() {
    return CarrierState::Clockwise;
}
