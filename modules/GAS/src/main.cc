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
#include "data-logger.hh"
#include "alarm.hh"
#include "mq5.hh"

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
    auto cs = target::pin_out(target::pins::d7);
    auto alarmled = target::pin_out(target::pins::d8);
    auto a = target::pin_out(target::pins::d13);

    // Initialize classes
    SdSpi sd(cs, spiBus);
    auto logger = DataLogger(sd);
    Alarm alarm = Alarm(105, alarmled);
    Mq5 mq5 = Mq5(sensor);

    // Initialize variables
    int mq5Value = 0;
    char charValue[3];

    // Startup blink
    a.set(0);
    hwlib::wait_ms(200);
    a.set(1);
    hwlib::wait_ms(100);
    a.set(0);

    //start loop
    hwlib::cout << "Writing to sd card\r\n";
    using namespace hwlib;
    while (true) {
        uint64_t time = hwlib::now_us();

        //read mq-5 sensor
        mq5Value = mq5.getSensorPercentage();
        convertToChar(mq5Value, charValue);

        //print value, write it to sd card and check if alarm needs to go off
        hwlib::cout << mq5Value << "\t";
        logger.writeValue(mq5Value);
        alarm.checkGasValue(mq5Value);

        hwlib::wait_us((int_fast32_t)(2000000 - (hwlib::now_us() - time)));
    }

    return 0;
}