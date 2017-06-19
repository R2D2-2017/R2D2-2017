#include "idle-state.hh"
using namespace Carrier;

IdleState::IdleState(CarrierController* controller) {
    this->controller = controller;
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller->getMotorController()->stop();
}

void IdleState::update() {

}

CarrierState IdleState::getState() {
    return CarrierState::Idle;
}
