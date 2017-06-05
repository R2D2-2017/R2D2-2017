#include "robot-arm.hh"

RobotArmController::RobotArmController(stepper &x_axis, stepper &y_axis, stepper &z_axis,
                                       hwlib::target::pin_in &xLimitSwitch, hwlib::target::pin_in &yLimitSwitch,
                                       Ky101 &ky101) :
    x_axis(x_axis),
    y_axis(y_axis),
    z_axis(z_axis),
    xLimitSwitch(xLimitSwitch),
    yLimitSwitch(yLimitSwitch),
    ky101(ky101) {}

void RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {
    int selectedMicroSteps = (axis == RobotAxis::Z) ? microStepsBase : microStepsArms;
    int requiredSteps      = (int)(selectedMicroSteps * (degrees * armStepRatio) / stepSize);

    for (uint16_t stepsTaken = 0; stepsTaken < requiredSteps; stepsTaken++) {
        // TODO add limitation check
        switch (axis) {
        case RobotAxis::X:
            if ((checkLimitations() == RobotLimitSwitch::BOTH ||
                 checkLimitations() == RobotLimitSwitch::X)   &&
                !clockwise) {

                break;
            }
            x_axis.step(clockwise);
            break;
        case RobotAxis::Y:
            if ((checkLimitations() == RobotLimitSwitch::BOTH ||
                 checkLimitations() == RobotLimitSwitch::Y)   &&
                !clockwise) {
                break;
            }
            y_axis.step(clockwise);
            break;
        case RobotAxis::Z:
            z_axis.step(clockwise);
            break;
        }
    }
}

RobotLimitSwitch RobotArmController::checkLimitations() {
    if (!xLimitSwitch.get() && !yLimitSwitch.get()) {
        return RobotLimitSwitch::BOTH;
    } else if (!xLimitSwitch.get()) {
        return RobotLimitSwitch::X;
    } else if (!yLimitSwitch.get()) {
        return RobotLimitSwitch::Y;
    } else {
        return RobotLimitSwitch::NONE;
    }
}

// The amounts of steps in rotateAxis functions is yet to be determined through testing.
// TODO test variables
void RobotArmController::startup() {
    while (!ky101.get()) {
        rotateAxis(RobotAxis::Z, 1, true);
    }
    while (!xLimitSwitch.get()) {
        rotateAxis(RobotAxis::X, 1, true);
    }
    while (!yLimitSwitch.get()) {
        rotateAxis(RobotAxis::Y, 1, true);
    }
}
