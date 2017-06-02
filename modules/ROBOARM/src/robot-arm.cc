#include "robot-arm.hh"
RobotArmController::RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis,
                                       hwlib::target::pin_in &firstStepperSwitch,
                                       hwlib::target::pin_in &secondStepperSwitch,
                                       KY101 &ky101) :
        x_axis(x_axis),
        y_axis(y_axis),
        z_axis(z_axis),
        firstStepperSwitch(firstStepperSwitch),
        secondStepperSwitch(secondStepperSwitch),
        ky101(ky101){

}


void RobotArmController::reset() {

}

void RobotArmController::rotateAxis(RobotAxis axis, int degrees, bool clockwise) {

    int requiredSteps = microStepsArms * (degrees * armStepRatio) / stepSize;
    if(axis == RobotAxis::Z) {
      requiredSteps = microStepsBase * (degrees * baseStepRatio) / stepSize;
    }
    for(uint16_t stepsTaken = 0; stepsTaken<requiredSteps; stepsTaken++) {
        //TODO add limitation check
        switch (axis) {
            case RobotAxis::X:
                x_axis.step(clockwise);
                break;
            case RobotAxis::Y:
                y_axis.step(clockwise);
                break;
            case RobotAxis::Z:
                z_axis.step(clockwise);
                break;

        }
    }
}

int RobotArmController::checkLimitations() {
    if (!firstStepperSwitch.get() && !secondStepperSwitch.get()) {
        return 3;
    } else if (!firstStepperSwitch.get()) {
        return 1;
    } else if (!secondStepperSwitch.get()) {
        return 2;
    } else {
        return 0;
    }

}

void RobotArmController::startup(){
    while(!ky101.get()) {
        rotateAxis(RobotAxis::Z, 1, 1);
    }
    while(!())
};