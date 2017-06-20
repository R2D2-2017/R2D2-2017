#pragma once
#include "../carrier-controller.hh"
#include "i-carrier-state.hh"
#include "../hc-sr04.hh"
namespace Carrier {

/**
 * \brief Forward declaration of the CarrierController class
 */
    class CarrierController;

    class AvoidanceState : public ICarrierState {
    private:
        /// Reference of the CarrierController so it can be used in the states
        CarrierController *controller;
        /// Threshold for the distance between the sensor and the object
        int threshold = 25;
    public:
        /**
         * \brief Constructor for the AvoidanceState
         * @param controller
         */
        AvoidanceState(CarrierController *controller, HcS);

        void update();

        CarrierState getState();

    };

}