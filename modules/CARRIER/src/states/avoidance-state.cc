
#include "avoidance-state.hh"
using namespace Carrier;

AvoidanceState::AvoidanceState(CarrierController *controller): controller(controller) {

}


CarrierState AvoidanceState::getState() {
    return CarrierState::Avoidance;
}

void AvoidanceState::update() {
    if (north.getDistance() <= threshold) {
        controller->getMotorController()->stop(controller->getSpeed());
        while (!(south.getDistance() <= threshold)) {
            controller->getMotorController()->left(controller->getSpeed());
        }
    }


}
