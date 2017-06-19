#include "backward-state.hh"
using namespace Carrier;

CounterClockwiseState::CounterClockwiseState(CarrierController* controller) : controller(controller) {
    // if (controller->sonarSensor.getDistance() <= distThreshold) {
        // controller->setState(new IdleState(controller));
    // }
     controller->getMotorController()->left(controller->getSpeed());
}

void CounterClockwiseState::update() {

}

CarrierState CounterClockwiseState::getState() {
    return CarrierState::CounterClockwise;
}
