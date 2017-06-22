
#include "avoidance-state.hh"
using namespace Carrier;

AvoidanceState::AvoidanceState(CarrierController &controller): ICarrierState(controller) {

}

void AvoidanceState::update() {
    if (controller.getSonarValue(SonarDirection::North)[0] <= threshold) {
        controller.getMotorController().stop();
        while (controller.getSonarValue(SonarDirection::South)[0] > threshold) {
            controller.getMotorController().left(controller.getSpeed());
        }
    }


}

CarrierState AvoidanceState::getState() {
    return CarrierState::Avoidance;
}