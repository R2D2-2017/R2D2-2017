/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \author    David Driessen
 * \author    Paul Ettema
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \author	  Bram van Btrgeijk
 * \author	  Wilco Louwerse
 * \author    David de Jong
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
#include <fatfs.hh>

/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *		  The characters are stored in the second parameter
 *		  mq5Char.
 */
void convertToChar(int mq5Value, char mq5Char[3]);

void convertToChar(int mq5Value, char mq5Char[3]){
    mq5Char[0] = ((char)(mq5Value / 100 % 10) + '0');
    mq5Char[1] = ((char)(mq5Value % 100 / 10) + '0');
    mq5Char[2] = ((char)(mq5Value % 10 ) + '0');
}

int main(){
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Setup pins
    target::pin_adc sensor = target::pin_adc(target::ad_pins::a0);
    target::spi_bus_due spiBus;
    target::pin_out cs(target::pins::d7);

    // alarm leds
    target::pin_out greenAlarmLed(target::pins::d10);
    target::pin_out yellowAlarmLed(target::pins::d9);
    target::pin_out redAlarmLed(target::pins::d8);

    // speaker sound players
    target::pin_out warningSpeakerPin(target::pins::d11);
    target::pin_out dangerSpeakerPin(target::pins::d12);

    // flash led
    target::pin_out startLed(target::pins::d13);

    // thresholds
    int warningThreshold = 0;
    int dangerThreshold = 120;


    // Initialize classes
    SdSpi sd(cs, spiBus);
    Speaker warningPlayer( warningSpeakerPin );
    Speaker dangerPlayer( dangerSpeakerPin );
    Alarm alarm(warningThreshold, dangerThreshold, greenAlarmLed, yellowAlarmLed, redAlarmLed, warningPlayer, dangerPlayer);

    Mq5 mq5(        sensor);
    MuStore::FatFs fileSystem(&sd);
    MuStore::FsError err;

    MuStore::FsNode dataFile = fileSystem.get("/data.txt", err);
    hwlib::cout << "\r\n";
    hwlib::cout << (int)err << "\r\n";

    //check if the filesystem is correct
    hwlib::cout << fileSystem.getFsType() << "\r\n";
    hwlib::cout << (int)fileSystem.getFsSubType() << "\r\n";

    //check if the file is present on the sd
    if(!dataFile.doesExist()) {
        hwlib::cout << "data.txt does not exist \r\n";
    }

    // Initialize variables
    int mq5Value = 0;
    char charValue[3];
    char sessionSeparator[] = "\r\n=========================\r\n";

    // Startup blink
    startLed.set(0);
    hwlib::wait_ms(200);
    startLed.set(1);
    hwlib::wait_ms(100);
    startLed.set(0);

    //seek EOF to append data instead of overwriting it.
    dataFile.seek(dataFile.getSize());

    //Write separation line between measurement sessions.
    dataFile.write(sessionSeparator, sizeof(sessionSeparator), err);

    //start loop
    hwlib::cout << "Writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();

        //read mq-5 sensor
        mq5Value = mq5.getSensorPercentage();
        convertToChar(mq5Value, charValue);

        //write it to sd card and check if alarm needs to go off
        dataFile.write(charValue, 3, err);
        hwlib::cout << "wiring data 0 for success: " << (int)err << "\r\n";
        dataFile.write("\r\n", 2, err);
        hwlib::cout << "wiring newline 0 for success: " << (int)err << "\r\n";
        alarm.checkGasValue(mq5Value);
        hwlib::cout << (mq5Value) << "\r\n";


        //print error value of the write action
        //hwlib::cout << (int)err << "\r\n";

        hwlib::wait_us((int_fast32_t)(2000000 - (hwlib::now_us() - time)));
    }

    return 0;
}