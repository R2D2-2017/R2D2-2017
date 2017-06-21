/**
 * \file
 * \brief     The declarations of the class Mq5 of GAS-02, used for reading the mq-5 gas sensor.
 * \author    Wilco Louwerse
 * \author	  Bram van bergeijk
 * \author    Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      https://github.com/R2D2-2017/R2D2-2017/wiki/MQ-5-gas-sensor
 * \trello    http://bit.ly/2sSmQjw
 */

#pragma once

#include "wrap-hwlib.hh"

class Mq5 {
public:

    /**
    * \brief Constructor for Mq5.
    *
    * Initializes the sensor adc pin and sets the calibration value by using readSensorAverage(25,0.2).
    * \param sensor       The analog pin the gas sensor is connected to.
    * \param meanFilter   The strictness of the mean-filter used on the average calculation.
    */
    Mq5(hwlib::target::pin_adc &sensor, float meanFilter = 0.2f)
    		: sensor(sensor), meanFilter(meanFilter) {}

    /**
    * \brief Reads the gas sensor using readGasSensorAverage(sensor, 5).
    *
    * Compares the returned value of this to the calibration value
    * and returns a percentage (100 if equal to calibration value).
    * \return A percentage which is equal to 100 when the read value is equal to the calibration value.
    */
	int getSensorPercentage();

    /**
    * \brief Getter for a calibration function that also calculates it.
    *
    * \return The calibration value.
    */
    float getCalibrationValue();

	/**
	* \brief Calibrates the sensor to the given value.
	*
	* \param value The value to be set.
	*/
    void setMq5CalibrationValue(float value);

    /**
    * \brief   Gets the isCalibrated bool.
    *
    * \return  The isCalibrated bool.
    */
    bool getMq5IsCalibrated();

    /**
    * \brief   Sets the isCalibrated bool.
    *
    * \param calibrated    The desired state of the bool.
    */
    void setMq5IsCalibrated(bool calibrated);

private:

    const float newMax = 3.3f;

    /**
     * integer value to get the numbers behind the floating point into an integer.
     */
    const int floatMultp = 1000;

    /**
    * The pin the mq-5 sensor is connected to.
    */
    hwlib::target::pin_adc &sensor;

    /**
    * The strictness of the mean-filter.
    */
    float meanFilter;

    /**
    * The calibration value read/set during startup.
    */
    float calibrationValue = 0;

    /**
    * Value that says uf the sensor has a calibration value.
    * False by default to prevent non calibrated initialization.
    */
    bool isCalibrated = false;

    /**
    * \brief Reads the gas sensor data.
    *
    * \return The measured data as float voltage.
    */
    float readSensor();

    /**
    * \brief Reads the gas sensor data 5 times and returns an average of the measured values.
    *
    * \param quantityCounter    The given amount of times the gas sensor is going to be measured.
    * \return                   The average measured data as float voltage.
    */
    float readSensorAverage(int quantityCounter);
};
