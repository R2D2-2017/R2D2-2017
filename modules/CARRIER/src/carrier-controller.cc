#include "carrier-controller.hh"

Carrier::CarrierController::CarrierController(MotorController & motorController,
    HcSr04 & sonarSensor, float distThreshold, int speed) :
    motorController{ motorController }, sonarSensor{  sonarSensor },
    distThreshold{ distThreshold }, speed{ speed }
{
    state = CarrierState::Driving;

    targetTime = startTime = std::chrono::steady_clock::now();
    // speed = 0.1; // m/s
    // distThreshold = 0.5; // meter
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
        motorController.stop();
        break;
    case CarrierState::Driving:
        if (sonarSensor.getDistance() <= distThreshold) {
            stop();
        }
        break;
    case CarrierState::Turning:
        break;
    case CarrierState::Sensing:
        break;
    }
}

void Carrier::CarrierController::forward(float distance) {
    if (sonarSensor.getDistance() <= distThreshold) {
        stop();
    } else {
        state = CarrierState::Driving;
        motorController.forward(speed);
        startTime = std::chrono::steady_clock::now();
        targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(distance) + startTime.time_since_epoch());
    }
}

void Carrier::CarrierController::backward(float distance) {
    state = CarrierState::Driving;
    motorController.backward(speed);
    startTime = std::chrono::steady_clock::now();
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(distance) + startTime.time_since_epoch());
}

void Carrier::CarrierController::left(float degrees) {
    state = CarrierState::Turning;
    motorController.left(speed);
    startTime = std::chrono::steady_clock::now();
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(degrees) + startTime.time_since_epoch());
}

void Carrier::CarrierController::right(float degrees) {
    state = CarrierState::Turning;
    motorController.right(speed);
    startTime = std::chrono::steady_clock::now();
    targetTime = std::chrono::steady_clock::time_point(timeUntilDestination(degrees) + startTime.time_since_epoch());
}

void Carrier::CarrierController::setSpeed(float speed) {
    this->speed = speed;
}

void Carrier::CarrierController::stop() {
    state = CarrierState::Idle;
}
