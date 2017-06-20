/**
 * \file
 * \brief     The definitions of the mq-5 sensor functionality of GAS-02.
 * \author    Wilco Louwerse
 * \author	  Bram van bergeijk
 * \author    Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      https://github.com/R2D2-2017/R2D2-2017/wiki/MQ-5-gas-sensor
 * \trello    https://trello.com/c/FUDCRaeC/1-12-the-application-can-convert-the-analog-value-from-the-mq-5-to-percentage-value20
 */

#include "mq5.hh"
#include <cmath>

float Mq5::readSensor() {
    // float analogValue = ((((float)sensor.get()) / 4096.0f * 3.3f)*1000);
    // Raw sensor value casted to a float.
    float rawSensorValue = static_cast<float>(sensor.get());

    // Analog value of the sensor.
    float analogValue = (( rawSensorValue / (powf(2.0f, static_cast<float>(sensor.adc_n_bits))) * newMax)* floatMultp);
    hwlib::cout << static_cast<int>(analogValue) << "\n\r";
    return analogValue;
}


float Mq5::readSensorAverage(int quantityCounter) {
    float totalValue = 1;
    float sensorValue;
    for(int i = 1; i <= quantityCounter; i++){
        do {
            sensorValue = readSensor();
        } while((1+meanFilter) < (sensorValue / ((totalValue + sensorValue)/i))
        && (sensorValue / ((totalValue + sensorValue)/i))  < (1-meanFilter));

        totalValue += sensorValue;
        hwlib::wait_ms(200);
    }
    return totalValue/quantityCounter;
}

int Mq5::getSensorPercentage() {
    // percentage is divinding by 100
    return (int)(100 / calibrationValue * readSensorAverage(1));
}
float Mq5::getCalibrationValue(){
    int measurementQuantity = 200;
    return readSensorAverage(measurementQuantity);
}

void Mq5::setMq5CalibrationValue(float value){
    calibrationValue = value;
}

bool Mq5::getMq5Iscalibrated(){
    return isCalibrated;
}

void Mq5::setMq5Iscalibrated(bool calbrated){
    isCalibrated = calbrated;
}
