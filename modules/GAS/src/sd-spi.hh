/**
 * \file sd-spi.hh
 * \brief     SD SPI Store provider.
 * \author    Chris Smeele
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * SD SPI Store provider from https://github.com/cjsmeele/Picus ported to use
 * hwlib and work inside the R2D2 Project by Paul Ettema
 *
 * Original file is copyright 2016 (c) Chris Smeele and licensed under GPLv3.
 * This file is modified and relicensed under the Apache license with the
 * original author's permission.
 */
#pragma once

#include "wrap-hwlib.hh"

#include <store.hh>

/**
 * \brief Provides a SD SPI Block Storage Provider
 */
class SdSpi : public MuStore::Store {

public:
    /**
     * XXX Temporary: Needed for static arrays in data logger code.
     *                Remove when switching to filesystem usage!
     */
    static constexpr size_t tmpBlockSize = 512;
private:

    struct SdCommand {
        uint8_t cmd;
        uint32_t arg;
    };

    static const size_t cmdTimeoutClocks = 600;

    bool cardPresent = false;
    bool inited = false;

    /**
     * The cs the sd card is connected to
     */
    hwlib::pin_out &spiCs;
    /**
     * The spi bus the sd card is connected to
     */
    hwlib::spi_bus &spiBus;

    /**
     * \brief Wait for the sd card to become ready for accepting new commands.
     * \returns the value received from the spi bus
     */
    uint8_t wait();

    /**
     * \brief Sends a byte over the spi bus to the sd card reader
     * \param byte The byte to send to the sd card reader
     * \returns the byte received when sending the byte
     */
    uint8_t send(uint8_t byte);

    /**
     * \brief Sends an array of bytes over the spi bus to the sd card reader
     * \param buffer The array of bytes
     * \param length The length of the array
     */
    uint8_t send(uint8_t *buffer, size_t length);

    /**
     * \brief Sends a command to the sd card reader
     * \param cmd The command to send to the sd card
     * \returns The response byte on the command
     */
    uint8_t send(SdCommand cmd);

    /**
     * \brief Sends a block of data to the sd card
     * \param buffer The array of data to send
     * \param length The length of the array of data
     * \returns Returns the status code if the sending was successful or not
     */
    MuStore::StoreError sendBlock(const uint8_t *buffer, size_t length);

    /**
     * \brief Receives a response byte from the sd card reader
     * \returns The response byte
     */
    uint8_t recv();

    /**
     * \brief Receives an array of data from the sd card reader
     * \param buffer The array to store the data in
     * \param length The ammount of data to receive in bytes
     */
    void recv(uint8_t *buffer, size_t length);

    /**
     * \brief Receives a block of data from the sd card
     * \param buffer The array to store the data in
     * \param length The ammount of data to receive
     * \returns Returns the status code if the receiving was successful or not
     */
    MuStore::StoreError recvBlock(uint8_t *buffer, size_t length);

    /**
     * \brief Receives a response byte
     * \returns The response byte
     */
    uint8_t recvR1();

public:
    /**
     * \brief Seeks to a position within the sd card
     * \param lba The block to seek to onto the sd card
     * \returns Returns the status code if the seeking was successful or not
     */
    MuStore::StoreError seek(size_t lba);

    /**
     * \brief Reads a block from the sd card into a buffer
     * \param buffer The buffer to read the block into
     * \returns Returns the status code if the reading was successful or not
     */
    MuStore::StoreError read(void *buffer);

    /**
     * \brief Writes a block from a buffer to the sd card
     * \param buffer The buffer to read a block from
     * \returns Returns the status code if the writing was successful or not
     */
    MuStore::StoreError write(const void *buffer);

    using Store::read;
    using Store::write;

    /**
     * \brief Creates a SD SPI Block Provider
     * \param cs The CS pin the sd card reader is connected to
     * \param bus The spi bus the sd card reader is connected to
     */
    SdSpi(hwlib::pin_out &cs, hwlib::spi_bus &bus);
    ~SdSpi() = default;
};
