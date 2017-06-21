
#include "avoidance-state.hh"
using namespace Carrier;

AvoidanceState::AvoidanceState(CarrierController *controller): controller(controller) {

}


CarrierState AvoidanceState::getState() {
    return CarrierState::Avoidance;
}

void AvoidanceState::update() {
    if (controller.getSonarValue(SonarDirections::North)[0] <= threshold) {
        controller.getMotorController().stop(controller->getSpeed());
        while (controller.getSonarValue(SonarDirections::South)[0] > threshold) {
            controller.getMotorController().left(controller->getSpeed());
        }
    }


}

CarrierState AvoidanceState::getState() {
    return CarrierState::Avoidance;
}