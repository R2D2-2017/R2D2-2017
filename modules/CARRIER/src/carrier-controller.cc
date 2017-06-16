#include "carrier-controller.hh"
using namespace Carrier;

CarrierController::CarrierController(MotorController & motorController,
    HcSr04 & sonarSensor, float distThreshold, int speed) :
    motorController{ motorController }, sonarSensor{  sonarSensor },
    distThreshold{ distThreshold }, speed{ speed }
{
    state = new IdleState(this);

    targetTime = startTime = std::chrono::steady_clock::now();
    // speed = 0.1; // m/s
    // distThreshold = 0.5; // meter
}

CarrierController::~CarrierController() {
    stop();
}

CarrierState CarrierController::currentState() {
    return state->getState();
}

std::chrono::nanoseconds CarrierController::timeUntilDestination(float dist) {
    return std::chrono::nanoseconds(std::lround((dist / speed) * std::nano::den));
}

float CarrierController::distanceTraveled(std::chrono::time_point<std::chrono::steady_clock> elapsedTime) {
    return std::chrono::duration_cast<std::chrono::seconds>(elapsedTime.time_since_epoch()).count() * speed;
}

void CarrierController::update() {
   state->update();
}

void CarrierController::left(float degrees) {
    motorController.left(speed);
    startTime = std::chrono::steady_clock::now();
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(degrees) + startTime.time_since_epoch());
}

void CarrierController::right(float degrees) {
    motorController.right(speed);
    startTime = std::chrono::steady_clock::now();
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(degrees) + startTime.time_since_epoch());
}

void CarrierController::setState(CarrierState state) {
    switch(state) {
        case CarrierState::Forward:
            this->state = new ForwardState(this);
        break;
        
        case CarrierState::Backward:
            this->state = new BackwardState(this);
        break;

        case CarrierState::Idle:
            this->state = new IdleState(this);
        break;
    }
}

void CarrierController::setSpeed(float speed) {
    this->speed = speed;
}

MotorController* CarrierController::getMotorController() {
    return &motorController;
}

void CarrierController::stop() {
}
