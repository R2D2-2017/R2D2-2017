#include "carrierController.hh"

Carrier::CarrierController::CarrierController(/*Motor & motor,
    Sonar & sonar, */float distThreshold, float speed) :
    //motor{ motor }, sonar{ sonar },
    distThreshold{ distThreshold }, speed{ speed }
{
    state = CarrierState::Idle;

    targetTime = std::chrono::high_resolution_clock::now();
    //speed = 0.1; // m/s
    //distThreshold = 0.5; // meter
}

Carrier::CarrierController::~CarrierController() {
    stop();
}

Carrier::CarrierState Carrier::CarrierController::currentState() {
    return state;
}

std::chrono::nanoseconds Carrier::CarrierController::timeUntilDestination(float dist) {
    return std::chrono::nanoseconds(std::lround((dist / speed) * std::nano::den));
}

float Carrier::CarrierController::distanceTraveled(std::chrono::time_point<std::chrono::steady_clock> elapsedTime) {
    return std::chrono::duration_cast<std::chrono::seconds>(elapsedTime.time_since_epoch()).count() * speed;
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
    if (/*sonar.getDistance() <= distThreshold
        ||*/ targetTime <= std::chrono::high_resolution_clock::now()) {
        state = CarrierState::Idle;
    }
}

void Carrier::CarrierController::rotate() {
    
}

void Carrier::CarrierController::forward(float distance) {
    state = CarrierState::Driving;
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(distance) + std::chrono::high_resolution_clock::now().time_since_epoch());
    //motor.forward();
    //while (sonar.getDistance() <= distThreshold || startTime + estRemainingTime >= hwlib::now_us());
    //motor.stop();
}

void Carrier::CarrierController::backward(float distance) {
    state = CarrierState::Driving;
}

void Carrier::CarrierController::left(float degrees) {
    state = CarrierState::Turning;
}

void Carrier::CarrierController::right(float degrees) {
    state = CarrierState::Turning;
}

void Carrier::CarrierController::setSpeed(float speed) {
    this->speed = speed;
}

void Carrier::CarrierController::stop() {
    //motor.stop();
    state = CarrierState::Idle;
}
