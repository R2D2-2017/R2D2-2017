#pragma once

#include "i-carrier-state.hh"
#include "../carrier-controller.hh"
namespace Carrier {
class CarrierController;
class BackwardState : public ICarrierState {
    private:
        CarrierController* controller;
    public:
        BackwardState(CarrierController* controller);
        void update();
        CarrierState getState();
};

}
