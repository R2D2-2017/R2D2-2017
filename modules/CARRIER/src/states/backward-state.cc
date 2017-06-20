#include "backward-state.hh"
using namespace Carrier;

BackwardState::BackwardState(CarrierController &controller) : ICarrierState{ controller } {
    if (controller.getSonarValue(SonarDirections::South)[0] <= 50) {
        controller.setState(CarrierState::Idle);
        controller.getSerialCom().write("PATH OBSTRUCTED CANT GO BACKWARDS");
    } else {
        controller.getMotorController().backward(controller.getSpeed());
    }
}

void BackwardState::update() {
 if (controller.getSonarValue(SonarDirections::South)[0] <= 50) {
        controller.setState(CarrierState::Idle);
        controller.getSerialCom().write("PATH OBSTRUCTED CANT GO BACKWARDS");
    }
}

CarrierState BackwardState::getState() {
    return CarrierState::Backward;
}
