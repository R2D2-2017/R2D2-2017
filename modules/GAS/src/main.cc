/**
 * \file
 * \brief       GAS module main
 * \author      Chris Smeele
 * \author      David Driessen
 * \author      Paul Ettema
 * \author      Robbie Valkenburg
 * \author      Mike Hilhorst
 * \author      Bram van Bergeijk
 * \author      Wilco Louwerse
 * \author      David de Jong
 * \author      Nicky van Steensel van der Aa
 * \copyright   Copyright (c) 2017, The R2D2 Team
 * \license     See LICENSE
 *              https://github.com/R2D2-2017/R2D2-2017/wiki/Gas-safety-system
 *              https://trello.com/c/etqKmerH/93-gas-gas-safety-system
 */
#include "wrap-hwlib.hh"
#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "alarm.hh"
#include "mq5.hh"
#include "parser.hh"
#include "setup.hh"
#include <fatfs.hh>

/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *        The characters are stored in the second parameter
 *        mq5Char.
 */

static void intToString(unsigned int toConvert, char *converted) {
    converted[0] = ((char) (toConvert / 1000 % 10) + '0');
    converted[1] = ((char) (toConvert % 1000 / 100) + '0');
    converted[2] = ((char) (toConvert % 100 / 10) + '0');
    converted[3] = ((char) (toConvert % 10) + '0');
}

const char *dataFilePath = "/data.txt";
const char *confFilePath = "/conf.txt";
const char *calibFilePath = "/calib.txt";
const char *sessionSeparator = "\r\n=========================\r\n";

const int numberOfUnusedMatrices = 0;
const int numberOfMatrices = 4;
const int startupLedWait = 200;
const int preHeatTime = 120;    // Time in seconds for preheating of the sensor.
const int secondMs = 1000;


int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Gas pin.
    target::pin_adc sensor(target::ad_pins::a0);

    // Sd card pins.
    target::spi_bus_due spiBus;
    target::pin_out cs(target::pins::d7);

    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    // Alarm LED's.
    target::pin_out greenAlarmLed(target::pins::d22);
    target::pin_out yellowAlarmLed(target::pins::d24);
    target::pin_out redAlarmLed(target::pins::d26);

    // Speaker sound pins.
    target::pin_out warningSpeakerPin(target::pins::d11);
    target::pin_out dangerSpeakerPin(target::pins::d12);

    // Flash LED.
    target::pin_out startLed(target::pins::d13);

    // Initialize variables.
    int measureWaitTime = 2000000; // Default value to prevent cpu overuse when no value is given in the conf file.

    char charValue[4];
    char configurationInput[200]; // Buffer configuration file.

    // Initialize classes for writing and reading to/from files.
    SdSpi sd(cs, spiBus);
    MuStore::FatFs fileSystem(&sd);
    MuStore::FsError err;

    // Initialize classes for the alarm system.
    Speaker warningPlayer(warningSpeakerPin);
    Speaker dangerPlayer(dangerSpeakerPin);
    Alarm alarm(greenAlarmLed, yellowAlarmLed, redAlarmLed, warningPlayer, dangerPlayer);
    Mq5 mq5(sensor);
    Setup matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);

    // Startup blink.
    startLed.set(false);
    hwlib::wait_ms(startupLedWait);
    startLed.set(true);
    hwlib::wait_ms(startupLedWait);
    startLed.set(false);

    // Try to access conf.txt and data.txt and check if they are actually on the SD card.
    MuStore::FsNode dataFile = fileSystem.get(dataFilePath, err);

    if (err == MuStore::FsError::FS_ERR_OK) {
        hwlib::cout << "data.txt found.\r\n";
    } else {
        hwlib::cout << "Filesystem returned error: " << static_cast<int>(err) << "\r\n";
    }

    if (!dataFile.doesExist()) {
        hwlib::cout << "data.txt does not exist.\r\n";
    }

    MuStore::FsNode confFile = fileSystem.get(confFilePath, err);

    if (err == MuStore::FsError::FS_ERR_OK) {
        hwlib::cout << "conf.txt found.\r\n";
    } else {
        hwlib::cout << "Filesystem returned error: " << static_cast<int>(err) << "\r\n ";
    }

    if (!dataFile.doesExist()) {
        hwlib::cout << "conf.txt does not exist.\r\n";
    }

    for (int i = preHeatTime; i >= 0; --i) {
        intToString(i, charValue);
        matrix.displayString(charValue);
        hwlib::wait_ms(secondMs);
    }

    // Read data from configuration file.
    confFile.read(configurationInput, confFile.getSize(), err);
    if (sizeof(configurationInput) <= confFile.getSize()) {
        hwlib::cout << "Input buffer to small contact the developer of this program\r\n";
        return 0;
    }
    configurationInput[confFile.getSize()] = '\0';
    //hwlib::cout << configurationInput << "\r\n"; //debug statement for console output of read configuration
    if (!parseArray(configurationInput, measureWaitTime, alarm, mq5)) {
        return 0;
    }

    // Checks if the mq5 is calibrated and gets a calibration value if it is not calibrated.
    if (!mq5.isMq5Calibrated()) {
        char tempValueArray[4];

        hwlib::cout << "Sensor is not calibrated.\r\nCalibration will start\r\n";

        MuStore::FsNode calibFile = fileSystem.get(calibFilePath, err);

        if (err == MuStore::FsError::FS_ERR_OK) {
            hwlib::cout << "calib.txt found.\r\n";
        } else {
            hwlib::cout << "Filesystem returned error: " << static_cast<int>(err) << "\r\n ";
        }

        if (!dataFile.doesExist()) {
            hwlib::cout << "calib.txt does not exist.\r\n";
        }

        intToString(static_cast<int>(mq5.getCalibrationValue()), tempValueArray);
        calibFile.write(tempValueArray, sizeof(tempValueArray), err);
        hwlib::cout << "wiring data 0 for success: " << static_cast<int>(err) << "\r\n";
        calibFile.truncate();
        hwlib::cout << "Calibration done.\r\nCheck calib.txt for the value\r\n";
        return 0;
    }

    // Seek last entry in the data file and set the pointer.
    // To this location to append data instead of overwriting it.
    dataFile.seek(dataFile.getSize());

    // Write a separation line to the datafile to show where measurement sessions start and end.
    dataFile.write(sessionSeparator, sizeof(sessionSeparator), err);

    if (err != MuStore::FsError::FS_ERR_OK) {
        hwlib::cout << "Writing returned error: " << static_cast<int>(err) << "\r\n";
    }

    // Start loop measurements, writing data and alarm.
    hwlib::cout << "Writing to sd card\r\n";
    int mq5Value = 0;
    while (true) {
        uint64_t time = hwlib::now_us();

        // Read mq-5 sensor and send value to alarm and LED matrices.
        mq5Value = mq5.getSensorPercentage();
        intToString(mq5Value, charValue);
        matrix.displayString(charValue);
        alarm.checkGasValue(mq5Value);

        // Write it to sd card.
        dataFile.write(charValue, sizeof(charValue), err);
        dataFile.write("\r\n", 1, err);
        hwlib::wait_us((int_fast32_t) (measureWaitTime - (hwlib::now_us() - time)));
    }

    return 0;
}
