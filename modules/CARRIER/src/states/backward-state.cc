#include "backward-state.hh"
using namespace Carrier;

BackwardState::BackwardState(CarrierController* controller) : controller(controller) {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller->getMotorController()->backward(100);
}

void BackwardState::update() {
    
}

CarrierState BackwardState::getState() {
    return CarrierState::Backward;
}