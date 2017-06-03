#include "robot-arm.hh"
RobotArmController::RobotArmController(Stepper &x_axis, Stepper &y_axis, Stepper &z_axis, hwlib::target::pin_in &firstStepperSwitch, hwlib::target::pin_in &secondStepperSwitch, KY101 &ky101) :
        x_axis(x_axis),
        y_axis(y_axis),
        z_axis(z_axis),
        xLimitSwitch(xLimitSwitch),
        yLimitSwitch(yLimitSwitch),
        ky101(ky101)
        {}


void RobotArmController::reset() {
    rotateAxis(RobotAxis::Y, 250, false);
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
                if((checkLimitations() == 3 || checkLimitations() == 1) && !clockwise) {
                    break;
                }
                x_axis.step(clockwise);
                break;
            case RobotAxis::Y:
                if((checkLimitations() == 3 || checkLimitations() == 2) && !clockwise) {
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

int RobotArmController::checkLimitations() {
    if (!xLimitSwitch.get() && !yLimitSwitch.get()) {
        return 3;
    } else if (!xLimitSwitch.get()) {
        return 1;
    } else if (!yLimitSwitch.get()) {
        return 2;
    } else {
        return 0;
    }

}

void RobotArmController::startup(){
    while(!ky101.get()) {
        rotateAxis(RobotAxis::Z, 1, 1);
    }
    while(!xLimitSwitch.get()){
        rotateAxis(RobotAxis::);
    }
    while(!yLimitSwitch.get()){
        rotateAxis(RobotAxis::);
    }
};