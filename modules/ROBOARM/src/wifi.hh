/**
 * \file
 * \brief     Wifi module
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include "wrap-hwlib.hh"

/**
 * \brief Temporary wifi test code (to be removed before merge)
 */
void temp_wifi_main();

/**
 * Wifi class implementing the ESP8266 to create a wifi network and receive
 * commands through it
 */
class Wifi {
    bool debug = true;
    /**
     * The client id to response to
     */
    char id_last_transmition = '0';
    /**
     * UART input pin the ESP8266 is connected to
     */
    hwlib::pin_in &rx;

    /**
     * UART output pin the ESP8266 is connected to
     */
    hwlib::pin_out &tx;

    /**
     * Size of the buffer containing the last received response
     */
    static const int bufferSize = 512;

    /**
     * Buffer containing the last received response
     */
    char buffer[bufferSize];

    /**
     * \brief Sends a string to the wifi module, to end the command send \r\n
     */
    void AT(const hwlib::string<32> &command);

    /**
     * \brief Receive a response to a command and store it in the internal buffer
     */
    void receive();

public:
    Wifi(hwlib::pin_in &rx, hwlib::pin_out &tx);

    /**
     * \brief Gets the firmware version of the wifi module
     */
    void getVersion();

    /**
     * \brief Gets the current mode (AP or client)
     */
    void getMode();

    /**
     * \brief Gets current access point settings
     */
    void getAccessPoint();

    /**
     * \brief Gets ip addresses of clients connected to the access point
     */
    void getIpAddresses();

    /**
     * \brief Gets own ip address
     */
    void getIpAddress();

    /**
     * \brief Sets up an access point
     * \param ssid The ssid for the access point
     * \param password The password for the access point
     */
    void setupAccessPoint(const hwlib::string<16> &ssid,
                          const hwlib::string<16> &password);

    /**
     * \brief Sets the wifi module to multiple connections or single connection
     * \param multiple If true up to 4 connections can be made, when false only
     * one
     */
    void multipleConnections(bool multiple);

    /**
     * \brief Sets the transfer mode to normal transmission mode
     */
    void setTransferMode();

    /**
     * \brief Starts a server on port 333
     */
    void startServer();

    /**
     * \brief Stops the server on port 333
     */
    void stopServer();

    /**
     * \brief Receives data from the server
     */
    hwlib::string<16> receiveData();

    void send(const hwlib::string<16> &data);
};
