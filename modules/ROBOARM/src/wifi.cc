/**
 * \file
 * \brief     Wifi module
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "wifi.hh"

Wifi::ATSTATUS Wifi::AT(const hwlib::string<32> &command) {
    ATSTATUS atstatus = ATSTATUS::NO_CHANGE;
    for (size_t i = 0; i < command.length(); i++) {
        hwlib::uart_putc_bit_banged_pin(command[i], tx);
    }
    hwlib::uart_putc_bit_banged_pin('\r', tx);
    hwlib::uart_putc_bit_banged_pin('\n', tx);
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
        if (c == '\n' && i >= 3) {
            if (buffer[i - 3] == 'y') {
                atstatus = ATSTATUS::READY;
                break;
            } else if (buffer[i - 3] == 'K') {
                atstatus = ATSTATUS::OK;
                break;
            } else if (buffer[i - 3] == 'R') {
                atstatus = ATSTATUS::ERROR;
                break;
            } else if (buffer[i - 3] == 'e') {
                atstatus = ATSTATUS::NO_CHANGE;
                break;
            }
        }
    }

    if (debug) {
        hwlib::cout << "Response:\r\n--------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
    }

    return atstatus;
}

Wifi::ATSTATUS Wifi::setupAccessPoint(const hwlib::string<16> &ssid,
                                      const hwlib::string<16> &password) {
    hwlib::string<32> at = "AT+CWSAP=\"";
    at += ssid;
    at += "\",\"";
    at += password;
    at += "\",5,3";
    return AT(at);
}

hwlib::string<16> Wifi::getVersion() {
    if (AT("AT+GMR") == ATSTATUS::OK) {
        hwlib::string<16> ip;
        int begin = 0;
        for (int i = 0; i < bufferSize; ++i) {
            if (begin == 2) {
                if (buffer[i] == '\n') {
                    break;
                }
                ip += buffer[i];
            } else if (buffer[i] == ':') {
                begin++;
            }
        }
        return ip;
    }
    return "";
}

void Wifi::getMode() {
    AT("AT+CWMODE?");
}

hwlib::string<32> Wifi::getAccessPoint() {
    if (AT("AT+CWSAP?") == ATSTATUS::OK) {
        hwlib::string<32> ip;
        bool begin = false;
        for (int i = 0; i < bufferSize; ++i) {
            if (begin) {
                if (buffer[i] == '\n') {
                    break;
                }
                ip += buffer[i];
            } else if (buffer[i] == ':') {
                begin = true;
            }
        }
        return ip;
    }
    return "";
}

hwlib::string<32> Wifi::getIpAddresses() {
    if (AT("AT+CWLIF") == ATSTATUS::OK) {
        hwlib::string<32> addresses;
        bool begin = false;
        for (int i = 0; i < bufferSize; ++i) {
            if (begin) {
                if (buffer[i] == ',') {
                    begin = false;
                    addresses += '\n';
                    continue;
                }
                if (buffer[i] == '\n') {
                    break;
                }
                addresses += buffer[i];
            } else if (buffer[i] == '\n') {
                begin = true;
            }
        }
        return addresses;
    }
    return "";
}

hwlib::string<16> Wifi::getIpAddress() {
    if (AT("AT+CIFSR") == ATSTATUS::OK) {
        hwlib::string<16> ip;
        bool begin = false;
        for (int i = 0; i < bufferSize; ++i) {
            if (begin) {
                if (buffer[i] == '"') {
                    break;
                }
                ip += buffer[i];
            } else if (buffer[i] == '"') {
                begin = true;
            }
        }
        return ip;
    }
    return "";
}

void Wifi::multipleConnections(bool multiple) {
    if (multiple) {
        AT("AT+CIPMUX=1");
    } else {
        AT("AT+CIPMUX=0");
    }
}

void Wifi::setTransferMode() {
    AT("AT+CIPMODE=0");
}

void Wifi::startServer() {
    stopServer();

    setTransferMode();

    multipleConnections(true);

    AT("AT+CIPSTO?");

    hwlib::cout << "Starting Server\r\n";

    AT("AT+CIPSERVER=1");

    hwlib::cout << "Running!\r\n";
}

void Wifi::stopServer() {
    AT("AT+CIPSERVER=0");

    multipleConnections(false);
}

hwlib::string<32> Wifi::receive() {
    //index in the buffer
    int i = 0;

    //last index used to find the response at the end of the string faster
    buffer[i] = '\x0';
    char c;
    int begin = 0;
    int end = 0;

    // wait for response
    while (i < bufferSize - 2) {
        c = hwlib::uart_getc_bit_banged_pin(rx);

        //skip 0 bytes
        if (!c) continue;

        if (begin == 0 && c == '+') {
            begin = i;
        }

        buffer[i++] = c;
        //begin of transmition
        if (begin != 0 && i >= begin + 6 && c == ':') {
            end = i;
            break;
        }
    }
    // parse data length
    int dataLen = 0;
    for (int j = begin + 7; j < end - 1; ++j) {
        dataLen = dataLen * 10;
        dataLen += buffer[j] - '0';
    }

    // parse data
    bool done = false;
    hwlib::string<16> returnData;
    while (i < bufferSize - 2 && dataLen > i - end) {
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
    }
    buffer[i] = '\x0';

    if (debug) {
        hwlib::cout << "Data:\r\n----------------------------------\r\n";
        hwlib::cout << buffer;
        hwlib::cout << "---------------" << i << "---------------\r\n";
    }

    id_last_transmition = buffer[begin + 5];

    return returnData;
}

void Wifi::send(const hwlib::string<32> &data) {
    hwlib::string<48> s = "AT+CIPSEND=";
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
    AT(s);
    AT(data);
}

Wifi::Wifi(hwlib::pin_in &rx, hwlib::pin_out &tx) :
        rx(rx), tx(tx) {
    //Give ESP more than enough time to boot
    hwlib::wait_ms(500);
}

void Wifi::enDebug() {
    debug = true;
}
