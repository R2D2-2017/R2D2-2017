#pragma once
#include "../carrier-controller.hh"
#include "i-carrier-state.hh"
namespace Carrier {

/**
 * \brief Forward declaration of the CarrierController class
 */
    class CarrierController;

    class AvoidanceState : public ICarrierState {
    private:
        /// Reference of the CarrierController so it can be used in the states
        CarrierController *controller;

        int threshold = 25;
    public:

        AvoidanceState(CarrierController *controller, HcS);

        void update();

        void leftCornerState();

        void rightCornerState();

        void valleyState();

        void deadEndState();

        void wallState();

        CarrierState getState();

    };

}