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

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

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
    for (int i = 0; i < 65; i++) {
        hwlib::cout << ".";
        logger.writeValue(0.0f);
        logger.writeValue(0.5f);
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
