#include "stepper.hh"

Stepper::Stepper(hwlib::target::pin_out &dir_pin, hwlib::target::pin_out &stp_pin) : dir_pin(dir_pin),
                                                                                     stp_pin(stp_pin) {
    stp_pin.set(0);
    dir_pin.set(1);
    
    speed = 0;
    maxSpeed = 300.0f;
    acceleration = 30.0f;

    targetPosition = 0;
    currentPosition = 0;

    lastStepTime = 0;
    minPulseWidth = 100;
    stepIntervalTime = 1000000 / maxSpeed;//0;
    clockwise = true;
}

void Stepper::step() {
    dir_pin.set(clockwise);
    stp_pin.set(1);
    hwlib::wait_us(minPulseWidth);
    stp_pin.set(0);
    currentPosition += clockwise ? 1 : -1;
}

void Stepper::setTarget(int amount, bool clockwise) {
    targetPosition = amount;
    this->clockwise = clockwise;
}

void Stepper::run() {
    if (!stepIntervalTime) {
        return;
    }

    unsigned long time = hwlib::target::now_us();
    if (time - lastStepTime >= stepIntervalTime) {
        step();
        lastStepTime = time;
    }
}

void Stepper::resetPosition() {
    currentPosition = 0;
    targetPosition = 0;
}

long Stepper::remainingDistance() {
    return targetPosition - currentPosition;
}

bool Stepper::inMotion() {
    return !(speed == 0.0f && targetPosition == currentPosition);
}
