#pragma once

#include "i-carrier-state.hh"
#include "../carrier-controller.hh"
namespace Carrier {
class CarrierController;

class IdleState : public ICarrierState {
    private:
        CarrierController* controller;
    public:
        IdleState(CarrierController* controller);
        void update();
        CarrierState getState();
};

}
