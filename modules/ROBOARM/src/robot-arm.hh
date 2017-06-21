/**
 * \file
 * \brief     Robot arm controller
 * \author    Bob Thomas
 * \author    Remco Ruttenberg
 * \author    Chris Smeele
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "ky101.hh"
#include "stepper.hh"
#include "wrap-hwlib.hh"
#include <tuple>

namespace RoboArm {
    /**
     * \brief Enum for the different step modes
     */
    enum RobotResolution {
        FULLSTEP      = 128,
        HALFSTEP      = FULLSTEP / 2,
        QUARTERSTEP   = FULLSTEP / 4,
        EIGHTHSTEP    = FULLSTEP / 8,
        SIXTEENTHSTEP = FULLSTEP / 16
    };

    /**
     * \brief Position type, used as input for coordinate-based movement.
     */
    struct Position {
        float x, y;
        float yRot;
    };

    /**
     * \brief Enum class for the different motors on the robot arm
     */
    enum class Motor {
        M1, M2, M3
    };

    /**
     * \brief Enum class for the different limit switches
     */
    enum class RobotLimitSwitch {
        BOTH, M1, M2, NONE
    };

    /// List of limits of M1, M2 and M3.
    static constexpr std::pair<float,float> motorLimits[] {
        {    0, 150 },
        {  -90,   0 },
        { -180, 180 },
    };

    /**
     * \brief Robot Arm Controller to control 3 different stepper motors.
     */
    class RobotArmController {

        /// microSteps the driver board is using to control the X and Y position.
        static constexpr int microStepsArms = EIGHTHSTEP;

        /// microSteps the driver board is using to control the Y axis rotation.
        static constexpr int microStepsBase = QUARTERSTEP;

        /// Length of the arm from the base joint to the middle joint.
        static constexpr float arm1Length = 18.5;

        /// Length of the arm from the middle joint to the hand.
        static constexpr float arm2Length = 21;

        /// How many teeth the driver gear of M3 has.
        static constexpr int smallBaseGear = 20;

        /// How many teeth the driver gear for the arms have for M1 and M2 (XY axes)
        static constexpr int smallArmGear = 11;

        /// How many teeth the driven gear has for all three axes
        static constexpr int bigGear = 45;

        /// The size of a step to turn the motor 1 degree
        static constexpr float stepSize = 1.65;

        /// Calculating the ratio to drive a gear correctly
        /// http://www.wikihow.com/Determine-Gear-Ratio
        static constexpr float baseStepRatio = bigGear / smallBaseGear;

        /// Calculating the ratio to drive a gear correctly
        /// http://www.wikihow.com/Determine-Gear-Ratio
        static constexpr float armStepRatio = bigGear / smallArmGear;

        /**
         * \brief The current rotations of M[123] in degrees.
         * These initial values match the motor rotations after startup.
         */
        std::tuple<float,float,float> motorRotations {150, 0, 0};

        /// The different stepper motors you can use.
        Stepper &m1Stepper, &m2Stepper, &m3Stepper;

        /// Input pins on which the M1 limit switch get wired to check limitation status
        hwlib::target::pin_in &m1LimitSwitch;

        /// Input pins on which the M2 limit switch get wired to check limitation status
        hwlib::target::pin_in &m2LimitSwitch;

        /// Input pins on which the M3 limit switch get wired to check limitation status
        hwlib::target::pin_in &m3LimitSwitch;

        /// Class that reads input to see if the base is on it's starting position for Yrot.
        Ky101 ky101;

    public:
        /**
         * \brief Constructor for the Robot arm controller
         *
         * \param[in]  m1Stepper  stepper motor 1 - controls joint 1
         * \param[in]  m2Stepper  stepper motor 1 - controls joint 2
         * \param[in]  m3Stepper  stepper motor 1 - controls Y axis rotation
         * \param[in]  m1LimitSwitch  pin on which the limit switch for M1 is wired
         * \param[in]  m2LimitSwitch  pin on which the limit switch for M2 is wired
         * \param[in]  m3LimitSwitch  pin on which the limit switch for M3 is wired
         * \param[in]  ky101 class that's used to determine the start position for m3
         */
        RobotArmController(Stepper &m1Stepper,
                           Stepper &m2Stepper,
                           Stepper &m3Stepper,
                           hwlib::target::pin_in &m1LimitSwitch,
                           hwlib::target::pin_in &m2LimitSwitch,
                           hwlib::target::pin_in &m3LimitSwitch,
                           Ky101 &ky101);


        static std::tuple<float,float,float> positionToMotorRotations(Position pos);

        /**
         * \brief Check if the given rotation for the given motor is possible.
         *
         * \param motor   the motor
         * \param degrees the amount of degrees to turn
         *
         * \return whether the rotation is possible
         */
        bool canRotateMotor(Motor motor, int degrees) const;

        /**
         * \brief Rotate the given motor with the set amount of degrees.
         *
         * Note: A negative degree value means clockwise rotation.
         *
         * \param motor   The motor you want to rotate
         * \param degrees how many degrees you want to rotate
         *
         * \retval true  When rotation succeeded
         * \retval false When rotation failed (due to motor limits)
         */
        bool rotateMotor(Motor motor, int degrees);

        /**
         * \brief Move the hand to the given position by turning the arm's motors.
         *
         * Note: yRot is given in degrees.
         *
         * \param[in] pos The new position
         *
         * \retval true  Move succeeded.
         * \retval false Movement failed, destination out of reach.
         */
        bool moveTo(Position pos);

        /**
         * \brief Set up the robot at its starting position.
         */
        void startup();

        /**
         * \brief Enable the robot arm's motors.
         */
        void enable();

        /**
         * \brief Disable the robot arm's motors.
         */
        void disable();

        /**
         * \brief Function check if the robot has reached its limitations
         *
         * \return enum value based on which switch is pressed
         */
        RobotLimitSwitch checkLimitations();
    };
}
