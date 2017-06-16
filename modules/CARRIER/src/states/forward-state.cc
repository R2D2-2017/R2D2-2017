#include "forward-state.hh"
using namespace Carrier;

ForwardState::ForwardState(CarrierController* controller) : controller(controller) {    
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
    //  controller->getMotorController()->forward(100);
}

void ForwardState::update() {
    controller->getMotorController()->forward(100);
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
}

CarrierState ForwardState::getState() {
    return CarrierState::Forward;
}