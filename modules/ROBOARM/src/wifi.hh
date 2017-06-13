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

class Wifi {
    hwlib::pin_in& rx;
    hwlib::pin_out& tx;

    /**
     * \brief Sends a string to the wifi module, to end the command send \r\n
     */
    void send(const hwlib::string<16> &command);

    /**
     * \brief Receive a response to a command
     */
    void receive();

public:
    Wifi(hwlib::pin_in& rx, hwlib::pin_out& tx) :
    rx(rx), tx(tx) { }

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
    void receiveData();
};
