/**
 * \file
 * \brief     This is a module for reading the KY-024 Hall Sensor.
 * \author    Luke Roovers
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "hallsensor.hh"


HallSensor::HallSensor( int & hallSensorPin ):
    hallSensorPin ( hallSensorPin  )
{}



bool HallSensor::get(){
    // set pin
    pinMode (hallSensorPin, INPUT);
    
    value = digitalRead(hallSensorPin);
    return value;

}

