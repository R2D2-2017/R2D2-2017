/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \author    David Driessen
 * \author    Paul Ettema
 * \author	  Bram van Btrgeijk
 * \author	  Wilco Louwerse
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wrap-hwlib.hh"

#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "alarm.hh"
#include "mq5.hh"

#include <store.hh>
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
    target::pin_out alarmLed(target::pins::d8);
    target::pin_out startLed(target::pins::d13);

    // Initialize classes
    SdSpi sd(cs, spiBus);
    MuStore::FatFs fileSystem(&sd);
    MuStore::FsError err;

    MuStore::FsNode dataFile = fileSystem.get("/data.txt", err);
    hwlib::cout << "\r\n";
    hwlib::cout << (int)err << "\r\n";

    if(!dataFile.doesExist()) {
        hwlib::cout << "data.txt does not exist \r\n";
    }

    hwlib::cout << fileSystem.getFsType() << "\r\n";
    hwlib::cout << (int)fileSystem.getFsSubType() << "\r\n";

    Alarm alarm = Alarm(2.7f, alarmLed);
    Mq5 mq5 = Mq5(sensor);

    // Initialize variables
    int mq5Value = 0;
    char charValue[3];

    // Startup blink
    startLed.set(0);
    hwlib::wait_ms(200);
    startLed.set(1);
    hwlib::wait_ms(100);
    startLed.set(0);

    //start loop
    hwlib::cout << "Writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();

        //read mq-5 sensor
        mq5Value = mq5.getSensorPercentage();
        convertToChar(mq5Value, charValue);

        //print value, write it to sd card and check if alarm needs to go off
        hwlib::cout << charValue << "\r\n";
        dataFile.write(charValue, 3, err);

        hwlib::cout << (int)err << "\r\n";

        //alarm.checkGasValue(mq5Value);

        hwlib::wait_us((int_fast32_t)(2000000 - (hwlib::now_us() - time)));
    }

    return 0;
}
