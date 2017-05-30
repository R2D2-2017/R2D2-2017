/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wrap-hwlib.hh"

#include "hwlib-due-spi.hh"
#include "sd-spi.hh"
#include "data-logger.hh"
#include "alarm.hh"

float readGasSensor(hwlib::target::pin_adc &sensor) {
    return ((float) sensor.get()) / 4095.0f * 3.3f;
}

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::target::pin_adc sensor = hwlib::target::pin_adc(
            hwlib::target::ad_pins::a0);
    namespace target = hwlib::target;
    auto a = target::pin_out(target::pins::d13);
    a.set(0);
    hwlib::wait_ms(200);
    a.set(1);
    hwlib::wait_ms(100);
    a.set(0);

    auto cs = target::pin_out(target::pins::d7);

    target::spi_bus_due spiBus;
    SdSpi sd(cs, spiBus);

    auto logger = DataLogger(sd);

    hwlib::cout << "start\r\n";

    // Test writing to sd card

    hwlib::cout << "writing to sd card\r\n";
    // Write slightly more than one block
    for (int i = 0; i < 65; ++i) {
        uint64_t time = hwlib::now_us();
        hwlib::cout << ".";
//        hwlib::cout << (int)(readGasSensor(sensor)*100) << "\r\n"; //debug
        logger.writeValue(readGasSensor(sensor));
        checkGasValue(readGasSensor(sensor));
        hwlib::wait_us((int_fast32_t) (5000000 - (hwlib::now_us() - time)));
    }

    hwlib::cout << "done\r\n";

    while (true) {
        hwlib::wait_ms(100);
        a.set(0);
        hwlib::wait_ms(100);
        a.set(1);
    }

    return 0;
}
