//===------------ sd-spi.hh - SD SPI Block Storage Provider -----*- C++ -*-===//
//
//                              The R2D2 Project
//
// This file is distributed under the Apache License 2.0, See LICENSE for
// details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the SD SPI Block Storage Provider class.
///
//===----------------------------------------------------------------------===//
#pragma once

#include "wrap-hwlib.hh"

#include <store.hh>

/// \brief Provides a SD SPI Block Storage Provider
class SdSpi : public MuStore::Store {

    struct SdCommand {
        uint8_t cmd;
        uint32_t arg;
    };

    static const size_t cmdTimeoutClocks = 600;

    bool cardPresent = false;
    bool inited = false;

    /// The sclk the sd card is connected to
    hwlib::target::pin_out spiSclk;
    /// The mosi the sd card is connected to
    hwlib::target::pin_out spiMosi;
    /// The miso the sd card is connected to
    hwlib::target::pin_in spiMiso;
    /// The cs the sd card is connected to
    hwlib::target::pin_out spiCs;
    /// The spi bus created from the above pins
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spiBus;

    /// Wait for the sd card to become ready for accepting new commands.
    /// \returns the value received from the spi bus
    uint8_t wait();

    /// Sends a byte over the spi bus to the sd card reader
    /// \param byte The byte to send to the sd card reader
    /// \returns the byte received when sending the byte
    uint8_t send(uint8_t byte);

    /// Sends an array of bytes over the spi bus to the sd card reader
    /// \param buffer The array of bytes
    /// \param length The length of the array
    uint8_t send(uint8_t *buffer, size_t length);

    /// Sends a command to the sd card reader
    /// \param cmd The command to send to the sd card
    /// \returns The response byte on the command
    uint8_t send(SdCommand cmd);

    /// Sends a block of data to the sd card
    /// \param buffer The array of data to send
    /// \param length The length of the array of data
    /// \returns Returns the status code if the sending was successful or not
    MuStore::StoreError sendBlock(const uint8_t *buffer, size_t length);

    /// Receives a response byte from the sd card reader
    /// \returns The response byte
    uint8_t recv();

    /// Receives an array of data from the sd card reader
    /// \param buffer The array to store the data in
    /// \param length The ammount of data to receive in bytes
    void recv(uint8_t *buffer, size_t length);

    /// Receives a block of data from the sd card
    /// \param buffer The array to store the data in
    /// \param length The ammount of data to receive
    /// \returns Returns the status code if the receiving was successful or not
    MuStore::StoreError recvBlock(uint8_t *buffer, size_t length);

    /// Receives a response byte
    /// \returns The response byte
    uint8_t recvR1();

public:
    /// Seeks to a position within the sd card
    /// \param lba The block to seek to onto the sd card
    /// \returns Returns the status code if the seeking was successful or not
    MuStore::StoreError seek(size_t lba);

    /// Reads a block from the sd card into a buffer
    /// \param buffer The buffer to read the block into
    /// \returns Returns the status code if the reading was successful or not
    MuStore::StoreError read(void *buffer);

    /// Writes a block from a buffer to the sd card
    /// \param buffer The buffer to read a block from
    /// \returns Returns the status code if the writing was successful or not
    MuStore::StoreError write(const void *buffer);

    using Store::read;
    using Store::write;

    SdSpi();
    ~SdSpi() = default;
};
