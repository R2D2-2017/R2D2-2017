#include "stepper.hh"

Stepper::Stepper(hwlib::target::pin_out &dir_pin, hwlib::target::pin_out &stp_pin) : dir_pin(dir_pin),
                                                                                     stp_pin(stp_pin) {

    stp_pin.set(0);
    dir_pin.set(1);
    
    speed = 0;
    maxSpeed = 1.0f;
    acceleration = 0.0f;

    targetPosition = 0;
    currentPosition = 0;

    lastStepTime = 0;
    minPulseWidth = 1000;
    stepIntervalTime = 0;// 1000000 / maxSpeed;//0;
    clockwise = true;

    stepsTaken = 0;
    firstStepTime = 0.0f;
    prevStepTime = 0.0f;
    minStepTime = 1.0f;//10000000 / maxSpeed; // 1.0f
    setAcceleration(1);
}

void Stepper::calculateSpeed() {
    long remaining = remainingDistance();
    long stepsUntilStop = (long)((speed * speed) / (2.0f * acceleration));

    if (remaining > 0 && stepsUntilStop <= 1) {
        // Target reached, stopping
        stepIntervalTime = 0;
        speed = 0.0f;
        stepsTaken = 0;
        return;
    }

    if (remaining > 0) {
        // Move clockwise
        if (stepsTaken > 0) {
            // Currently accelerating
            if (stepsUntilStop >= remaining) {
                stepsTaken = -stepsUntilStop;
            }
        } else if (stepsTaken < 0) {
            // Currently decelerating
            if (stepsUntilStop < remaining) {
                stepsTaken = -stepsTaken;
            }
        }
    } else if (remaining < 0) {
        // Move counterclockwise
        if (stepsTaken > 0) {
            // Currently accelerating
            if (stepsUntilStop >= -remaining) {
                stepsTaken = -stepsUntilStop;
            }
        } else if (stepsTaken < 0) {
            if (stepsUntilStop < -remaining) {
                stepsTaken = -stepsTaken;
            }
        }
    }

    auto max = [](float a, float b) {
        return a > b ? a : b;
    };

    // First step, accelerate or decelerate
    if (stepsTaken == 0) {
        prevStepTime = firstStepTime;
    } else {
        prevStepTime -= (2.0f * prevStepTime) / ((4.0f * stepsTaken) + 1);
        prevStepTime = max(prevStepTime, minStepTime);
    }
    ++stepsTaken;
    stepIntervalTime = prevStepTime;
    speed = 1000000.0f / prevStepTime;

    if (clockwise) {
        speed = -speed;
    }
}

void Stepper::setAcceleration(float acceleration) {
    if (acceleration == 0.0) {
        return;
    }
    if (acceleration < 0.0) {
        acceleration = -acceleration;
    }

    // Babylonian method used for sqrt as hwlib does not contain it
    auto sqrt = [](const float num) {
        float i = 0;
        float x1, x2;
        while ((i * i) <= num) {
            i += 0.1f;
        }
        x1 = i;
        for (int j = 0; j < 10; ++j) {
            x2 = num;
            x2 /= x1;
            x2 += x1;
            x2 /= 2;
            x1 = x2;
        }
        return x2;
    };

    if (this->acceleration != acceleration) {
        stepsTaken *= (this->acceleration / acceleration);
        firstStepTime = 0.676 * sqrt(2.0f / acceleration) * 1000000.0f;
        this->acceleration = acceleration;
        calculateSpeed();
    }
}

void Stepper::setMaxSpeed(float speed) {
    if (speed < 0.0f) {
        speed = -speed;
    }
    if (maxSpeed != speed) {
        maxSpeed = speed;
        minStepTime = 1000000.0f / speed;
        if (stepsTaken > 0) {
            stepsTaken = (long)((speed * speed) / (2.0f * acceleration));
            calculateSpeed();
        }
    }
}

void Stepper::step() {
    dir_pin.set(clockwise);
    stp_pin.set(1);
    hwlib::wait_us(minPulseWidth);
    stp_pin.set(0);
    currentPosition += clockwise ? 1 : -1;
}

void Stepper::setTarget(int amount, bool clockwise) {
    currentPosition = 0;
    targetPosition = clockwise ? amount : -amount;
    this->clockwise = clockwise;
}

void Stepper::run() {
    if (!stepIntervalTime || currentPosition == targetPosition) {
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
