#include "carrierController.hh"

Carrier::CarrierController::CarrierController(/*Motor & motor,
    Sonar & sonar, */float distThreshold, float speed) :
    //motor{ motor }, sonar{ sonar },
    distThreshold{ distThreshold }, speed{ speed }
{
    state = CarrierState::Idle;
}

Carrier::CarrierController::~CarrierController() {
    stop();
}

Carrier::CarrierState Carrier::CarrierController::currentState() {
    return state;
}

uint64_t Carrier::CarrierController::timeUntilDestination(float dist)
{
    return 0;
}

void Carrier::CarrierController::update() {
    switch (state) {
    case CarrierState::Idle:
        break;
    case CarrierState::Driving:
        move();
        break;
    case CarrierState::Turning:
        rotate();
        break;
    case CarrierState::Sensing:
        break;
    }
}

void Carrier::CarrierController::move() {

}

void Carrier::CarrierController::rotate() {
    
}

void Carrier::CarrierController::forward(float distance) {
    //motor.forward();
    //while (sonar.getDistance() <= distThreshold || startTime + estRemainingTime >= hwlib::now_us());
    //motor.stop();
}

void Carrier::CarrierController::backward(float distance) {
    
}

void Carrier::CarrierController::left(float degrees) {

}

void Carrier::CarrierController::right(float degrees) {

}

void Carrier::CarrierController::setSpeed(float speed) {
    this->speed = speed;
}

void Carrier::CarrierController::stop() {
    //motor.stop();
    state = CarrierState::Idle;
}
