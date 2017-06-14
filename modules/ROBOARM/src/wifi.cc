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

    w.multipleConnections(true);

    w.startServer();

    w.getIpAddress();

    hwlib::cout << "Done!\r\n";

    hwlib::wait_ms(3000);

    hwlib::cout << "Receiving:\r\n";
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

void Wifi::setTransferMode() {
    send("AT+CIPMODE=0\r\n");

    receive();
}

void Wifi::startServer() {
    stopServer();

    setTransferMode();

    send("AT+CIPSTO?\r\n");
    receive();

    send("AT+CIPDINFO=1\r\n");
    receive();

    hwlib::cout << "Starting Server\r\n";

    send("AT+CIPSERVER=1\r\n");

    receive();

    hwlib::cout << "Running!\r\n";
}

void Wifi::stopServer() {
    send("AT+CIPSERVER=0\r\n");

    receive();
}

void Wifi::receiveData() {
     send("AT+CIPSTATUS\r\n");
     receive();

     //temporary status code parser
     hwlib::cout << "Status: [" << buffer[22] << "]\r\n";
     switch (buffer[22]) {
         case '2': hwlib::cout << "Waiting for connection\r\n"; break;
         case '3': hwlib::cout << "TCP Connection active\r\n"; break;
         case '4': hwlib::cout << "TCP Connection disconnected\r\n"; break;
         default: hwlib::cout << "Unknown status code\r\n"; break;
     }

     //if status is active tcp connection try to receive data
     if (buffer[22] == '3') {
         //receive 30 bytes from connection 0
         send("+IPD,0,30\r\n");
         receive();
     }
}

void Wifi::receive() {
    //index in the buffer
    int i = 0;

    //last index used to find the response at the end of the string faster
    buffer[i] = '\x0';
    char c;

    while (i < bufferSize - 1) {
        c = hwlib::uart_getc_bit_banged_pin(rx);

        //skip 0 bytes
        if (!c) continue;

        buffer[i++] = c;
        buffer[i] = '\x0';
        //end of response if buffer ends with y (ready), K (OK), R (ERROR) or
        //e (no change)
        if (c == '\n' && i >= 3 &&
            (buffer[i - 3] == 'y' ||
             buffer[i - 3] == 'K' ||
             buffer[i - 3] == 'R' ||
             buffer[i - 3] == 'e')) break;
    }
    //temporary print of responses if response end was found according to
    //comment above
    if (buffer[i - 3] == 'y' ||
        buffer[i - 3] == 'K' ||
        buffer[i - 3] == 'R' ||
        buffer[i - 3] == 'e') {
        hwlib::cout << "Response:\r\n--------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
    }
}
