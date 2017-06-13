/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \author    David Driessen
 * \author    Paul Ettema, Bram van bergeijk, Wilco Louwerse
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wrap-hwlib.hh"

#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "data-logger.hh"
#include "alarm.hh"

// TODO: Move to separate file (Temporary warning fix)
/**
 * \brief Reads the gas sensor data.
 * \param sensor 	The analog pin the gas sensor is connected to.
 * \returns The measured data as float voltage.
 */
float readGasSensor(hwlib::target::pin_adc &sensor);

/**
 * \brief Reads the gas sensor data a given amount of times and returns an average of the read values.
 * \param sensor 			The analog pin the gas sensor is connected to.
 * \param quantityCounter 	The given amount of times the gas sensor is gonne be read.
 * \returns The average measured data as float voltage.
 */
float readGasSensorAverage(hwlib::target::pin_adc &sensor, int quantityCounter);

/**
 * \brief Reads the gas sensor using readGasSensorAverage(sensor, 5), 
 *		  compares the returned value of this to the given calibration value 
 *		  and returns a percentage (100 if equel to calibration value).
 * \param sensor 			The analog pin the gas sensor is connected to.
 * \param calibrationValue	The calibration value read during startup.
 * \returns A percentage which is equal to 100 when the read value is equal to the calibration value.
 */
int compareToCalibration(hwlib::target::pin_adc &sensor, float calibrationValue);

float readGasSensor(hwlib::target::pin_adc &sensor) {
    // 4096.0f is previous max value
    // 3.3f is new max value
    float analogValue = (((float)sensor.get()) / 4096.0f * 3.3f);
    return analogValue;
}

float readGasSensorAverage(hwlib::target::pin_adc &sensor, int quantityCounter) {
    float totalValue = 0;
    for(int i = 0; i < quantityCounter; i++){
        totalValue += readGasSensor(sensor);
        hwlib::wait_ms(200);
    }
    return totalValue/quantityCounter;
}

int compareToCalibration(hwlib::target::pin_adc &sensor, float calibrationValue) {
    return (int)(100 / calibrationValue * readGasSensorAverage(sensor, 5));
}

int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Setup pins
    target::pin_adc sensor = target::pin_adc(target::ad_pins::a0);
    target::spi_bus_due spiBus;
    auto cs = target::pin_out(target::pins::d7);
    auto alarmled = target::pin_out(target::pins::d8);
    auto a = target::pin_out(target::pins::d13);

    // Initialize classes
    SdSpi sd(cs, spiBus);
    auto logger = DataLogger(sd);

    Alarm alarm = Alarm(2.7f, alarmled);
	hwlib::cout << "Calibrating...\r\n";
    float calibrationValue = readGasSensorAverage(sensor, 25);
	hwlib::cout << "Done Calibrating!\r\n\n";
    int sensorValue = 0;
    // Startup blink
    a.set(0);
    hwlib::wait_ms(200);
    a.set(1);
    hwlib::wait_ms(100);
    a.set(0);
    hwlib::cout << "Writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();
        // For debugging print a . for each measurement
        sensorValue = compareToCalibration(sensor, calibrationValue);
        cout << sensorValue << "%" << "\t";
        logger.writeValue(sensorValue);
        alarm.checkGasValue(sensorValue);

        hwlib::wait_us((int_fast32_t) (2000000 - (hwlib::now_us() - time)));
    }

    return 0;
}
