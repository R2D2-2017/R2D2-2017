/**
 * \file
 * \brief     GAS module main
 * \author    Chris Smeele
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <memstore.hh>
#include "wrap-hwlib.hh"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    namespace target = hwlib::target;
    auto a = target::pin_out(target::pins::d13);
    a.set(0);
    hwlib::wait_ms(500);
    a.set(1);
    hwlib::wait_ms(500);
    a.set(0);

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

    while (true) {
        hwlib::wait_ms(200);
        a.set(0);
        hwlib::wait_ms(500);
        a.set(1);
    }

    return 0;
}
