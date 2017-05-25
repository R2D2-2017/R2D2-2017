/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <memstore.hh>
#include "wrap-hwlib.hh"

#include "sd-spi.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;
    auto a = target::pin_out(target::pins::d13);
    a.set(0);
    hwlib::wait_ms(500);
    a.set(1);
    hwlib::wait_ms(500);
    a.set(0);

    auto sclk = target::pin_out(target::pins::sck);
    auto mosi = target::pin_out(target::pins::mosi);
    auto miso = target::pin_in(target::pins::miso);
    auto cs = target::pin_out(target::pins::d50);
    auto spiBus = hwlib::spi_bus_bit_banged_sclk_mosi_miso(sclk, mosi, miso);
    SdSpi sd(cs, spiBus);

    hwlib::cout << "start\r\n";

    // Test MuStore with memory store backend.

    char mem[1024];
    MuStore::MemStore store(mem, 1024);

    char buf[512] = {"hoi"};
    store.write(buf);

    buf[0] = '\0';

    store.rewind();
    store.read(buf);

    hwlib::cout << "read: <" << buf << ">\r\n";

    buf[0] = 'H';
    store.rewind();
    store.write(buf);

    buf[0] = '\0';

    store.rewind();
    auto x = store.read(buf);

    hwlib::cout << "read: <" << buf << "> (ret" << x << ")\r\n";
    hwlib::cout << "done\r\n";

    // Test writing to sd card

    hwlib::cout << "writing to sd card\r\n";
    char buffer[512] = {"Test string to write\0"};
    int ret = sd.write(0, buffer);
    hwlib::cout << "written with return code: " << ret << "\r\n";

    while (true) {
        hwlib::wait_ms(200);
        a.set(0);
        hwlib::wait_ms(500);
        a.set(1);
    }

    return 0;
}
