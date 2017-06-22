/**
 * \file
 * \brief     The definitions of the mq-5 sensor functionality of GAS-02.
 * \author    Wilco Louwerse
 * \author    Bram van bergeijk
 * \author    Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * https://github.com/R2D2-2017/R2D2-2017/wiki/MQ-5-gas-sensor
 * https://trello.com/c/FUDCRaeC/1-12-the-application-can-convert-the-analog-value-from-the-mq-5-to-percentage-value20
 */

#include "mq5.hh"
#include <cmath>

float Mq5::readSensor() {
    // Raw sensor value casted to a float.
    float rawSensorValue = static_cast<float>(sensor.get());

    // Analog value of the sensor.
    float analogValue = ((rawSensorValue / (powf(2.0f, static_cast<float>(sensor.adc_n_bits))) * newMax) * floatMultp);
    return analogValue;
}


float Mq5::readSensorAverage(int count) {
    float totalValue = 0;
    float sensorValue;
    for (int i = 1; i <= count; i++) {
        do {
            sensorValue = readSensor();
        } while ((1 + meanFilter) < (sensorValue / ((totalValue + sensorValue) / i))
                 && (sensorValue / ((totalValue + sensorValue) / i)) < (1 - meanFilter));

        totalValue += sensorValue;
        hwlib::wait_ms(200);
    }
    return totalValue / count;
}

int Mq5::getSensorPercentage() {
    // percentage is dividing by 100
    return (int) (100 / calibrationValue * readSensorAverage(1));
}

float Mq5::getCalibrationValue() {
    return readSensorAverage(200);
}

void Mq5::setMq5CalibrationValue(float value) {
    calibrationValue = value;
}

bool Mq5::isMq5Calibrated() {
    return isCalibrated;
}

void Mq5::setMq5IsCalibrated(bool calibrated) {
    isCalibrated = calibrated;
}
