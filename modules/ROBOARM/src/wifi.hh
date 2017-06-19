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
 * Wifi class implementing the ESP8266 to create a wifi network and receive
 * commands through it
 */
class Wifi {

    enum class ATSTATUS {
        OK,
        READY,
        ERROR,
        NO_CHANGE
    };

    bool debug = false;
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
     * \brief Send the AT command and stores it in the internal buffer
     * \return ATSTATUS The response status of the at command
     */
    Wifi::ATSTATUS AT(const hwlib::string<32> &command);

public:
    Wifi(hwlib::pin_in &rx, hwlib::pin_out &tx);

    /**
     * \brief Enable debug mode
     */
    void enDebug();

    /**
     * \brief Gets the firmware version of the wifi module
     * \return hwlib::string<16> The version of the firmware on the esp
     */
    hwlib::string<16> getVersion();

    /**
     * \brief Gets the current mode (AP or client)
     */
    void getMode();

    /**
     * \brief Gets current access point settings
     * \return hwlib::string<32> The AccessPoint settings
     */
    hwlib::string<32> getAccessPoint();

    /**
     * \brief Gets ip addresses of clients connected to the access point
     */
    hwlib::string<32> getIpAddresses();

    /**
     * \brief Gets own ip address
     * \return hwlib::string<16> The local ip address
     */
    hwlib::string<16> getIpAddress();

    /**
     * \brief Sets up an access point
     * \param ssid The ssid for the access point
     * \param password The password for the access point
     * \return ATSTATUS The response status of the at command
     */
    Wifi::ATSTATUS setupAccessPoint(const hwlib::string<16> &ssid,
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
     * \brief Waits for a transmition from a client
     * \return hwlib::string<32> The data received from the client
     */
    hwlib::string<32> receive();

    /**
     * \brief Sends a transmition back to the client
     */
    void send(const hwlib::string<32> &data);
};
