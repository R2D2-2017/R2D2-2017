/**
 * \file data-logger.cc
 * \brief     Logs sensor data to the sd card
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "data-logger.hh"

void DataLogger::clearHeader() {
    for (unsigned int i = 0; i < sd.getBlockSize() / sizeof(uint32_t); i++) {
        header[i] = 0;
    }
}

void DataLogger::updateHeader() {
    header[0] = totalMeasurements;
    header[1] = blockIndex;
}

void DataLogger::loadHeader() {
    sd.read(0, header);

    totalMeasurements = header[0];
    // If measurements is 0 handle it as an empty sd card and initialize with
    // default values
    if (totalMeasurements == 0) {
        blockIndex = 1;
        index = 0;
        return;
    }

    blockIndex = header[1];
    index = totalMeasurements % (sd.getBlockSize() / sizeof(float));
}

void DataLogger::clearBuffer() {
    for (unsigned int i = 0; i < sd.getBlockSize() / sizeof(float); i++) {
        buffer[i] = 0;
    }
}

void DataLogger::loadBuffer() {
    sd.read(blockIndex, buffer);
}

void DataLogger::writeValue(float value) {
    // Put the new value into the internal buffer and increase index and
    // measurements
    buffer[index] = value;
    index++;
    totalMeasurements++;

    // Write the updated buffer and header to the sd card
    sd.write(blockIndex, buffer);
    updateHeader();
    sd.write(0, header);

    // If the next index is overflowing move to next block
    if (index >= sd.getBlockSize() / sizeof(float)) {
        index = 0;
        blockIndex++;
        clearBuffer();
    }
}

DataLogger::DataLogger(SdSpi &sd)
    : sd(sd), totalMeasurements(0), index(0), blockIndex(1) {
    loadHeader();
    loadBuffer();
}
