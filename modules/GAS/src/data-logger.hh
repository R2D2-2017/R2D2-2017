/**
 * \file data-logger.hh
 * \brief     Logs sensor data to the sd card
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "sd-spi.hh"

class DataLogger {

    SdSpi& sd;
    uint32_t header[512 / sizeof(uint32_t)];
    float buffer[512 / sizeof(float)];
    unsigned int totalMeasurements;
    unsigned int index;
    unsigned int blockIndex;

    /// \brief Clears the internal header that is written to the sd card
    void clearHeader();

    /// \brief Updates the internal header
    void updateHeader();

    /// \brief Loads internal header from the sd card
    void loadHeader();

    /// \brief Clears the internal buffer that is written to the sd card
    void clearBuffer();

    /// \brief Loads the internal buffer from the sd card
    void loadBuffer();

public:
    /// \brief Logs a value onto the sd card
    /// \param The value to log
    void writeValue(float value);

    /// \brief Creates a data logger object to write sensor data to a sd card
    /// \param sd The SD card to write the data to
    DataLogger(SdSpi& sd);
};
