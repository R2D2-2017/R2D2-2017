#include "fast-cout.hh"
#include "wrap-hwlib.hh"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    hwlib::init(115200);
    while (true) {
        hwlib::cout << "hallo";
	    hwlib::cout << "a";
        hwlib::uart_putc('a');
        hwlib::wait_ms(500);
    }
}

#pragma clang diagnostic pop
