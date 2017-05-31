/**
 * \file
 * \brief     SD SPI Store provider.
 * \author    Chris Smeele
 * \author    Paul Ettema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 *
 * SD SPI Store provider from https://github.com/cjsmeele/Picus ported to use
 * hwlib and work inside the R2D2 Project by Paul Ettema
 *
 * Original file is copyright 2016 (c) Chris Smeele and licensed under GPLv3.
 * This file is modified and relicensed under the Apache license with the
 * original author's permission.
 */
#include "sd-spi.hh"

#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace MuStore;

///
/// \brief SD Card-Specific Data structure.
///
/// Fields are named as in the simplified SD spec.
///
/// Note: This bitfield struct serves only as documentation in this
/// file. It isn't used in code.
///
struct SdCsd {
    // Offset 0.
    uint8_t  version    : 2; // We don't support cards below version 2
                             // (value 0b01).
    uint8_t  _reserved1 : 6;

    // Offset 1.
    uint8_t  taac      : 8;
    uint8_t  nsac      : 8;
    uint8_t  tranSpeed : 8;

    // Offset 4.
    uint16_t ccc              : 12;
    uint8_t  readBlLen        :  4;

    // Offset 6.
    uint8_t  readBlPartial    :  1;
    uint8_t  writeBlkMisalign :  1;
    uint8_t   readBlkMisalign :  1;
    uint8_t  dsrImp           :  1;
    uint8_t  _reserved2       :  6;
    uint32_t cSize            : 22;

    // Offset 10.
    uint8_t  _reserved3       :  1;
    uint8_t  eraseBlkEn       :  1;
    uint8_t  sectorSize       :  7;
    uint8_t  wpGrpSize        :  7;

    // Offset 12.
    uint8_t  wpGrpEnable      :  1;
    uint8_t  _reserved4       :  2;
    uint8_t  r2wFactor        :  3;
    uint8_t  writeBlLen       :  4;
    uint8_t  writeBlPartial   :  1;
    uint8_t  _reserved5       :  5;

    // Offset 14.
    uint8_t  fileFormatGrp    :  1;
    uint8_t  copy             :  1;
    uint8_t  permWriteProtect :  1;
    uint8_t  tmpWriteProtect  :  1;
    uint8_t  fileFormat       :  2;
    uint8_t  _reserved6       :  2;

    // Offset 15.
    uint8_t  crc7             :  7;
    uint8_t  _endBit          :  1;
} __attribute__((packed));

uint8_t SdSpi::wait() {
    // Wait for the card to become ready for accepting new commands.
    uint8_t  x = 0;
    uint32_t i = 0;
    do {
        if (i++ > cmdTimeoutClocks)
            return x;
        uint8_t send_byte = 0xff;
        spiBus.write_and_read(spiCs, 1, &send_byte, &x);
    } while (x != 0xff);

    return x;
}

uint8_t SdSpi::recv() {
    return send(0xff);
}

void SdSpi::recv(uint8_t *buffer, size_t length) {
    for (size_t i = 0; i < length; i++)
        buffer[i] = recv();
}

StoreError SdSpi::recvBlock(uint8_t *buffer, size_t length) {
    size_t i = 0;
    uint8_t ch;

    do {
        if (i++ > cmdTimeoutClocks)
            return STORE_ERR_IO;
        // Wait for start block token (0xfe).
    } while ((ch = recv()) != 0xfe);

    for (i = 0; i < length; i++)
        buffer[i] = recv();

    return STORE_ERR_OK;
}

uint8_t SdSpi::recvR1() {
    // Receive R1 response byte.
    uint8_t  x = 0;
    uint32_t i = 0;
    do {
        if (i++ > cmdTimeoutClocks)
            return 0xff; // Invalid.
        uint8_t send_byte = 0xff;
        spiBus.write_and_read(spiCs, 1, &send_byte, &x);

        // First bit of R1 must be zero.
    } while (x & 0x80);

    return x;
}

uint8_t SdSpi::send(uint8_t byte) {
    uint8_t buffer;
    spiBus.write_and_read(spiCs, 1, &byte, &buffer);
    return (uint8_t) buffer;
}

uint8_t SdSpi::send(uint8_t *buffer, size_t length) {
    uint8_t ret = 0;
    for (size_t i = 0; i < length; i++)
        ret = send(buffer[i]);
    return ret;
}

uint8_t SdSpi::send(SdCommand cmd) {
    uint8_t str[6];
    str[0] = (uint8_t)(0x40 | (cmd.cmd & 0x3f));
    str[1] = (uint8_t)(cmd.arg >> 24);
    str[2] = (uint8_t)(cmd.arg >> 16);
    str[3] = (uint8_t)(cmd.arg >>  8);
    str[4] = (uint8_t)(cmd.arg      );

    if (cmd.cmd == 0) {
        str[5] = 0x95; // CRC7 for CMD0, includes terminating end bit.
    } else if (cmd.cmd == 8) {
        str[5] = 0x69; // CRC7 for CMD8 with 0x1a5 as params.
    } else {
        str[5] = 0xff; // ¯\_(ツ)_/¯
    }

    wait();
    send(str, sizeof(str));

    return recvR1();
}

StoreError SdSpi::sendBlock(const uint8_t *buffer, size_t length) {
    if (wait() != 0xff)
        return STORE_ERR_IO;

    send(0xfe); // Data start token.

    for (size_t i = 0; i < length; i++)
        send(buffer[i]);

    // CRC, unused.
    send(0xff);
    send(0xff);

    uint8_t respToken = recv();
    if ((respToken & 0x1f) == 0x05) {
        // 'Data accepted'.
        if (wait() != 0xff)
            return STORE_ERR_IO;

        return STORE_ERR_OK;
    } else {
        return STORE_ERR_IO;
    }
}

StoreError SdSpi::seek(size_t lba) {
    if (!cardPresent || !inited)
        return STORE_ERR_IO;
    if (lba >= blockCount)
        return STORE_ERR_OUT_OF_BOUNDS;

    pos = lba;

    return STORE_ERR_OK;
}

StoreError SdSpi::read(void *buffer) {
    if (!cardPresent || !inited)
        return STORE_ERR_IO;
    if (pos >= blockCount)
        return STORE_ERR_OUT_OF_BOUNDS;

    wait();

    // NOTE: SDHC/SDXC use LBAs, SDSC uses byte addresses.
    uint8_t result = send(SdCommand{17, (uint32_t)pos});
    if (result != 0) {
        return STORE_ERR_IO;
    }
    recvBlock((uint8_t*)buffer, blockSize);

    pos++;

    // Receive and discard 16-bit CRC.
    recv();
    recv();

    if (wait() != 0xff)
        return STORE_ERR_IO;

    return STORE_ERR_OK;
}

StoreError SdSpi::write(const void *buffer) {
    if (!cardPresent || !inited)
        return STORE_ERR_IO;
    if (pos >= blockCount)
        return STORE_ERR_OUT_OF_BOUNDS;

    if (wait() != 0xff)
        return STORE_ERR_IO;

    uint8_t result = send(SdCommand{24, (uint32_t)pos});
    if (result != 0) {
        return STORE_ERR_IO;
    }

    pos++;

    return sendBlock((uint8_t*)buffer, 512);
}

SdSpi::SdSpi(hwlib::pin_out &cs, hwlib::spi_bus &bus)
    : spiCs(cs),
      spiBus(bus) {

    // Dummy reset command, in case the card was in a strange state.
    send(SdCommand{0, 0});

    // Wait for the SD card to become ready.
    if (wait() != 0xff)
        return; // Probably no card present.

    cardPresent = true;

    uint8_t result;
    // Send CMD0, reset the card.
    result = send(SdCommand{0, 0});
    if (result != 1)
        return;

    // Check if the card can handle our voltage levels.
    result = send(SdCommand{8, 0x1a5});
    if (result != 1)
        return;

    {
        uint8_t cmd8Buf[4] = { };
        recv(cmd8Buf, 4);
        if ((cmd8Buf[2] & 0x0f) != 1)
            return; // Voltage range unacceptable.
        if (cmd8Buf[3] != 0xa5)
            return; // Check pattern mismatch.
    }

    // Wait for the card to leave idle state (wait for it to finish
    //                                        initializing).
    int j = cmdTimeoutClocks;
    do {
        if (j-- <= 0)
            return;
        result = send(SdCommand{55, 0});
        // Set the second highest bit to indicate SDHC/SDXC support.
        result = send(SdCommand{41, 1UL << 30});
    } while (result == 1);

    // Get Card-Specific Data.
    result = send(SdCommand{9, 0});
    if (result != 0)
        return;

    SdCsd csd;

    // For some reason bitfields are broken. We accecss it as a byte
    // array instead. Meh.
    uint8_t *csdb = (uint8_t*)&csd;
    recvBlock(csdb, sizeof(csd));

    if ((csdb[0] & 0xc0) == 0x40) {

    } else {
        return; // Currently no support for standard capacity.
    }

    blockSize  = 512;
    blockCount = (
          (uint32_t)(csdb[7] & 0x3f) << 16
        | (uint32_t)csdb[8] << 8
        | (uint32_t)csdb[9]
    ) * 1024;

    inited = true;
}
