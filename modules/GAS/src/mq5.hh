/**
 * \file
 * \brief     The declarations of the class Mq5 of GAS-02, used for reading the mq-5 gas sensor.
 * \author    Wilco Louwerse
 * \author	  Bram van bergeijk
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      https://github.com/R2D2-2017/R2D2-2017/wiki/MQ-5-gas-sensor
 * \trello    https://trello.com/c/FUDCRaeC/1-12-the-application-can-convert-the-analog-value-from-the-mq-5-to-percentage-value20
 */

#include "wrap-hwlib.hh"

class Mq5 {
public:

	/**
	 * \brief Constructor for Mq5
	 * Initializes the sensor adc pin and sets the calibration value by using readSensorAverage(25,0.2)
	 * \param sensor 	The analog pin the gas sensor is connected to.
	 * \param meanFilter The strictness of the mean-filter used on the average calculation
	 */
	Mq5(hwlib::target::pin_adc &sensor, float meanFilter)
			: sensor(sensor), meanFilter(meanFilter) {
		hwlib::cout << "Calibrating mq-5...\r\n";
		calibrationValue = readSensorAverage(25);
		hwlib::cout << "Done Calibrating mq-5!\r\n\n";
	}


	/**
	 * \brief Reads the gas sensor using readGasSensorAverage(sensor, 5),
	 *		  compares the returned value of this to the calibration value
	 *		  and returns a percentage (100 if equal to calibration value).
	 * \returns A percentage which is equal to 100 when the read value is equal to the calibration value.
	 */
	int getSensorPercentage();
    /**
     * \brief getter for a calibration function that also calculates it.
     * \param quantity  The number of measurements this function includes in its result. This is not used at the moment.
     * \preturns The calibration value
     */
    float getCalibrationValue(/*int quantity*/);

private:

	/**
     * The pin the mq-5 sensor is connected to
     */
	hwlib::target::pin_adc &sensor;

    /**
     * The strictness of the mean-filter
     */
    float meanFilter;

	/**
	 * The calibration value read/set during startup
	 */
	float calibrationValue = 0;

	/**
	 * \brief Reads the gas sensor data.
	 * \returns The measured data as float voltage.
	 */
	float readSensor();

	/**
	 * \brief Reads the gas sensor data 5 times and returns an average of the read values.
	 * \param quantityCounter 	The given amount of times the gas sensor is going to be read.
	 * \param meanFilter	The strictness of the mean-filter.
	 * \returns The average measured data as float voltage.
	 */
	float readSensorAverage(int quantityCounter);
};