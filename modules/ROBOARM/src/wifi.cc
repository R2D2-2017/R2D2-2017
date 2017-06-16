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

    w.getIpAddress();

    hwlib::cout << "Done!\r\n";

    hwlib::wait_ms(3000);

    hwlib::cout << "Receiving:\r\n";
    for (int i = 0; i < 600; i++) {
        hwlib::string<16> data = w.receiveData();
        if (data == "ping") {
            w.send("pong\n");
        }
    }

    w.stopServer();

    while (true) {
        hwlib::wait_ms(5000);
    }
}

void Wifi::AT(const hwlib::string<32> &command) {
    for (size_t i = 0; i < command.length(); i++) {
        hwlib::uart_putc_bit_banged_pin(command[i], tx);
    }
}

void Wifi::setupAccessPoint(const hwlib::string<16> &ssid,
                            const hwlib::string<16> &password) {
    AT("AT+CWSAP=\"");
    AT(ssid);
    AT("\",\"");
    AT(password);
    AT("\",5,3\r\n");

    receive();
}

void Wifi::getVersion() {
    AT("AT+GMR\r\n");

    receive();
}

void Wifi::getMode() {
    AT("AT+CWMODE?\r\n");

    receive();
}

void Wifi::getAccessPoint() {
    AT("AT+CWSAP?\r\n");

    receive();
}

void Wifi::getIpAddresses() {
    AT("AT+CWLIF\r\n");

    receive();
}

void Wifi::getIpAddress() {
    AT("AT+CIFSR\r\n");

    receive();
}

void Wifi::multipleConnections(bool multiple) {
    if (multiple) {
        AT("AT+CIPMUX=1\r\n");
    } else {
        AT("AT+CIPMUX=0\r\n");
    }

    receive();
}

void Wifi::setTransferMode() {
    AT("AT+CIPMODE=0\r\n");

    receive();
}

void Wifi::startServer() {
    stopServer();

    setTransferMode();

    multipleConnections(true);

    AT("AT+CIPSTO?\r\n");
    receive();

    hwlib::cout << "Starting Server\r\n";

    AT("AT+CIPSERVER=1\r\n");

    receive();

    hwlib::cout << "Running!\r\n";
}

void Wifi::stopServer() {
    AT("AT+CIPSERVER=0\r\n");
    receive();

    multipleConnections(false);
}

hwlib::string<16> Wifi::receiveData() {
    //index in the buffer
    int i = 0;

    //last index used to find the response at the end of the string faster
    buffer[i] = '\x0';
    char c;
    int begin = 0;
    int end = 0;

    // wait for response
    while (i < bufferSize - 1) {
        c = hwlib::uart_getc_bit_banged_pin(rx);

        //skip 0 bytes
        if (!c) continue;

        if (begin == 0 && c == '+') {
            begin = i;
        }

        buffer[i++] = c;
        buffer[i] = '\x0';
        //end of response if buffer ends with y (ready), K (OK), R (ERROR) or
        //e (no change)
        if (begin != 0 && i >= begin + 6 && c == ':') {
            end = i;
            break;
        }
    }
    // parse data length
    int dataLen = 0;
    for (int j = begin + 7; j < end - 1; ++j) {
        dataLen += buffer[j] - '0';
    }

    // parse data
    bool done = false;
    hwlib::string<16> returnData;
    while (i < bufferSize - 1 && dataLen > i - end) {
        c = hwlib::uart_getc_bit_banged_pin(rx);

        //skip 0 bytes
        if (!c) continue;

        buffer[i++] = c;
        if (!done) {
            if (c == '\n')
                done = true;
            else
                returnData += c;
        }
        buffer[i] = '\x0';
    }

    if (debug) {
        hwlib::cout << "Data:\r\n----------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
    }

    id_last_transmition = buffer[begin + 5];

    return returnData;
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
             buffer[i - 3] == 'e'))
            break;
    }

    if (debug) {
        hwlib::cout << "Response:\r\n--------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
    }
}

void Wifi::send(const hwlib::string<16> &data) {
    hwlib::string<32> s = "AT+CIPSEND=";
    s += id_last_transmition;
    s += ",";
    int len = data.length();
    if (len == 0)return;
    char buf[10] = "";
    int i = 9;
    for (; i >= 0 && len > 0; --i) {
        buf[i] = (char) (len % 10 + '0');
        len = len / 10;
    }
    i++;
    for (; i < 10; ++i) {
        s += buf[i];
    }
    s += "\r\n";
    AT(s);
    receive();
    AT(data);
    receive();
}

Wifi::Wifi(hwlib::pin_in &rx, hwlib::pin_out &tx) :
        rx(rx), tx(tx) {
    //Give ESP more than enough time to boot
    hwlib::wait_ms(500);
}
