/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \author    David Driessen
 * \author    Paul Ettema
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \author	  Bram van Bergeijk
 * \author	  Wilco Louwerse
 * \author    David de Jong
 * \author	  Nicky van Steensel van der Aa
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki	  https://github.com/R2D2-2017/R2D2-2017/wiki/Gas-safety-system
 * \trello	  https://trello.com/c/etqKmerH/93-gas-gas-safety-system
 */
#include "wrap-hwlib.hh"
#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "alarm.hh"
#include "speaker.hh"
#include "mq5.hh"
#include "parser.hh"
#include <fatfs.hh>
#include "setup.hh"

/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *		  The characters are stored in the second parameter
 *		  mq5Char.
 */
void convertToChar(int toConvert, char converted[4]);

void convertToChar(int toConvert, char converted[4]){
    converted[0] = ((char)(toConvert / 1000 % 10) + '0');
    converted[1] = ((char)(toConvert % 1000 / 100) + '0');
    converted[2] = ((char)(toConvert % 100 / 10) + '0');
    converted[3] = ((char)(toConvert % 10 ) + '0');
}

int main(){
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Setup pins
    target::pin_adc sensor = target::pin_adc(target::ad_pins::a0);
    target::spi_bus_due spiBus;
    target::pin_out cs(target::pins::d7);

    // matrix pins
    target::pin_out digitalIn( target::pins::d4 );
    target::pin_out chipSelect( target::pins::d5 );
    target::pin_out clock( target::pins::d6 );
    auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clock, digitalIn, hwlib::pin_in_dummy);




    // alarm leds
    target::pin_out greenAlarmLed(target::pins::d22);
    target::pin_out yellowAlarmLed(target::pins::d24);
    target::pin_out redAlarmLed(target::pins::d26);

    // speaker sound players
    target::pin_out warningSpeakerPin(target::pins::d11);
    target::pin_out dangerSpeakerPin(target::pins::d12);

    // flash led
    target::pin_out startLed(target::pins::d13);

    // Initialize variables
    int measureWaitTime             = 2000000; //default value to prevent cpu slurp.
    int mq5Value                    = 0;
    const int startupLedWait        = 200;

    // matrix settings
    int numberOfUnusedMatrices = 0;
    int numberOfMatrices = 4;

    char charValue[4];
    const char dataFilePath[]        = "/data.txt";
    const char confFilePath[]        = "/conf.txt";
    const char calibFilePath[]       = "/calib.txt";
    const char sessionSeparator[]    = "\r\n=========================\r\n";
    char configurationInput[200];

    // Initialize classes
    // Initialize classes for writing and reading from files
    SdSpi sd(cs, spiBus);
    MuStore::FatFs fileSystem(&sd);
    MuStore::FsError err;

    //Initialize classes for the alarm system
    Speaker warningPlayer( warningSpeakerPin );
    Speaker dangerPlayer( dangerSpeakerPin );
    Alarm alarm(greenAlarmLed, yellowAlarmLed, redAlarmLed, warningPlayer, dangerPlayer);
    Mq5 mq5(sensor);
    Setup matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);


    Parser parser(alarm, mq5, &measureWaitTime);

    hwlib::cout << (int)fileSystem.getFsSubType() << "\r\n";
    // Startup blink
    startLed.set(0);
    hwlib::wait_ms(startupLedWait);
    startLed.set(1);
    hwlib::wait_ms(startupLedWait);
    startLed.set(0);

    //Try to acces conf.txt and data.txt and check if they are actually on the SD card.
    MuStore::FsNode dataFile = fileSystem.get(dataFilePath, err);

    if (err == MuStore::FsError::FS_ERR_OK){
        hwlib::cout << "data.txt found.\r\n";
    } else {
        hwlib::cout << "Filesystem returned error: " <<(int)err << "\r\n";
    }

    if (!dataFile.doesExist()){
        hwlib::cout << "data.txt does not exist.\r\n";
    }


    MuStore::FsNode confFile = fileSystem.get(confFilePath, err);

    if (err == MuStore::FsError::FS_ERR_OK) {
        hwlib::cout << "conf.txt found.\r\n";
    } else {
        hwlib::cout << "Filesystem returned error: " <<(char)err << "\r\n ";
    }

    if (!dataFile.doesExist()) {
        hwlib::cout << "conf.txt does not exist.\r\n";
    }

    //read data from configuration file TODO make that thing propper size.
    confFile.read(configurationInput, confFile.getSize(), err);
    configurationInput[confFile.getSize()] = '\0';
    //hwlib::cout << configurationInput << "\r\n"; //debug statment for console output of read configuration
    parser.parseArray(configurationInput);


    //seek last entry in the data file and set the pointer
    //to this location to append data instead of overwriting it.
    dataFile.seek(dataFile.getSize());

    //Write a sepearation line to the datafile to show where measurement sessions start and end.
    dataFile.write(sessionSeparator, sizeof(sessionSeparator), err);

    if (err != MuStore::FsError::FS_ERR_OK) {
        hwlib::cout << "Writing returend error: " << (char)err << "\r\n";
    }

    //Checks if the mq5 is callibrated and gets a calibration value if it is not calibrated.
    if(!mq5.getMq5Iscalibrated()){
        char tempvaluearray[4];

        hwlib::cout << "Sensor is not calibrated.\r\nCallibration will start\r\n";

        MuStore::FsNode calibFile = fileSystem.get(calibFilePath, err);

        if (err == MuStore::FsError::FS_ERR_OK) {
            hwlib::cout << "calib.txt found.\r\n";
        } else {
            hwlib::cout << "Filesystem returned error: " <<(char)err << "\r\n ";
        }

        if (!dataFile.doesExist()) {
            hwlib::cout << "calib.txt does not exist.\r\n";
        }

        convertToChar((int)mq5.getCalibrationValue(), tempvaluearray);
        calibFile.write(tempvaluearray,sizeof(tempvaluearray) ,err);
        hwlib::cout << "wiring data 0 for success: " << (int)err << "\r\n";
        calibFile.truncate();
        hwlib::cout << "Calibration done.\r\nCheck calib.txt for the value\r\n";
        return 0;
    }

    //start loop
    hwlib::cout << "Writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();

        //read mq-5 sensor
        mq5Value = mq5.getSensorPercentage();
        convertToChar(mq5Value, charValue);
        matrix.operate(charValue);

        //write it to sd card and check if alarm needs to go off
        dataFile.write(charValue, sizeof(charValue), err);
        //hwlib::cout << "wiring data 0 for success: " << (int)err << "\r\n";
        dataFile.write("\r\n", 1, err);
        //hwlib::cout << "wiring newline 0 for success: " << (int)err << "\r\n";
        alarm.checkGasValue(mq5Value);
        //hwlib::cout << (mq5Value) << "\r\n";


        //print error value of the write action
        //hwlib::cout << (int)err << "\r\n";

        hwlib::wait_us((int_fast32_t)(measureWaitTime - (hwlib::now_us() - time)));
    }

    return 0;
}
