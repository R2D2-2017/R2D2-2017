#pragma once
#include "../carrier-controller.hh"
#include "i-carrier-state.hh"
namespace Carrier {
    
class CarrierController;
class ForwardState : public ICarrierState {
    private:
        CarrierController *controller;
    public:
        ForwardState(CarrierController *controller);
        void update();
        CarrierState getState();
        
};

}
