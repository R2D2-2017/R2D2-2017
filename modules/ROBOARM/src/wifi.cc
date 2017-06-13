/**
 * \file
 * \brief     Wifi module
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wifi.hh"

void temp_wifi_main() {
    auto wifiRx = hwlib::target::pin_in(hwlib::target::pins::d19);
    auto wifiTx = hwlib::target::pin_out(hwlib::target::pins::d18);

    auto w = Wifi(wifiRx, wifiTx);

    //Give ESP more than enough time to boot
    hwlib::wait_ms(500);

    w.getVersion();

    w.getMode();

    w.setupAccessPoint("ROBOARM", "123454321");

    w.getAccessPoint();

    w.getIpAddress();

    w.startServer();

    hwlib::cout << "Done!\r\n";

    for (int i = 0; i < 600; i++) {
        w.receiveData();
        hwlib::wait_ms(3000);
    }

    w.stopServer();

    while (true) {
        hwlib::wait_ms(5000);
    }
}

void Wifi::send(const hwlib::string<16> &command) {
    for (size_t i = 0; i < command.length(); i++) {
        hwlib::uart_putc_bit_banged_pin(command[i], tx);
    }
}

void Wifi::setupAccessPoint(const hwlib::string<16> &ssid,
                            const hwlib::string<16> &password) {
    send("AT+CWSAP=\"");
    send(ssid);
    send("\",\"");
    send(password);
    send("\",5,3\r\n");

    receive();
}

void Wifi::getVersion() {
    send("AT+GMR\r\n");

    receive();
}

void Wifi::getMode() {
    send("AT+CWMODE?\r\n");

    receive();
}

void Wifi::getAccessPoint() {
    send("AT+CWSAP?\r\n");

    receive();
}

void Wifi::getIpAddresses() {
    send("AT+CWLIF\r\n");

    receive();
}

void Wifi::getIpAddress() {
    send("AT+CIFSR\r\n");

    receive();
}

void Wifi::multipleConnections(bool multiple) {
    if (multiple) {
        send("AT+CIPMUX=1\r\n");
    } else {
        send("AT+CIPMUX=0\r\n");
    }

    receive();
}

void Wifi::startServer() {
    multipleConnections(false);

    send("AT+CIPSTO?\r\n");
    receive();

    send("AT+CIPSERVER=1\r\n");

    receive();
}

void Wifi::stopServer() {
    send("AT+CIPSERVER=0\r\n");

    receive();
}

void Wifi::receiveData() {
     send("+IPD,100\r\n");

     receive();
}

void Wifi::receive() {
    static char buffer[250];
    int i = 0;
    int li = 0;
    buffer[i] = '\x0';
    char c;

    while (i < 165) {
        c = hwlib::uart_getc_bit_banged_pin(rx);
        if (!c) continue;
        li = i;
        buffer[i++] = c;
        buffer[i] = '\x0';
        //end of response if buffer ends with y (ready), K (OK) or R (ERROR)
        if (c == '\n' && li >= 2 &&
            (buffer[li - 2] == 'y' ||
            buffer[li - 2] == 'K' ||
            buffer[li - 2] == 'R')) break;
    }
    //temporary print of responses if response end was found according to
    //comment above
    if (buffer[li - 2] == 'y' ||
        buffer[li - 2] == 'K' ||
        buffer[li - 2] == 'R') {
        hwlib::cout << "Response:\r\n--------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
        }
}
