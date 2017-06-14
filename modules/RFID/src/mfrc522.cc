/**
 *\file
 *\author Stefan de Beer, Arco Gelderblom
 *\copyright Copyright (c) 2017, The R2D2 Team
 *\license See LICENSE
 */

#include "mfrc522.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>

void Mfrc522::writeRegister(const mfrc522Registers reg, const uint8_t value){
    uint8_t address = static_cast<uint8_t>(reg);
    address <<= 1;
    uint8_t data[2] = {address, value}; // clearing address byte for writing
    wiringPiSPIDataRW (0, data, 2);
}

void Mfrc522::writeRegister(const mfrc522Registers reg, const uint8_t * value, const unsigned int len){
    for(uint8_t i = 0;i<len; i++){
      writeRegister(reg, value[i]);
    }
}

unsigned char Mfrc522::readRegister(const mfrc522Registers reg){
    uint8_t data[2];
    data[0] = 0x80 | (static_cast<uint8_t>(reg)<<1); //Setting address byte for reading
    wiringPiSPIDataRW(0, data, 2);
    return data[1];
}
  
void Mfrc522::setRegisterBitMask(const mfrc522Registers reg, const uint8_t mask){
    uint8_t buffer = readRegister(reg);
    writeRegister(reg, buffer|mask);
}

void Mfrc522::clearRegisterBitMask(const mfrc522Registers reg, const uint8_t mask){
    uint8_t buffer = readRegister(reg);
    buffer &= (~mask);
    writeRegister(reg, buffer);
}

void Mfrc522::softReset(){
  writeRegister(mfrc522Registers::command, static_cast<uint8_t>(mfrc522Commands::softReset)); //Send softReset command.
    delay(50); //wait while resetting.
    while(readRegister(mfrc522Registers::command)&(1<<4)); //wait for bit 4(powerDown bit) to clear if not reset yet.
}

void Mfrc522::init(){
    pinMode(6, OUTPUT); // The reset pin
    if(!digitalRead(6)){
        digitalWrite(6, HIGH);
        delay(50); //wait for mfrc522 to reset
    }else{
        softReset();
    }
    
    writeRegister(mfrc522Registers::tMode, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
    writeRegister(mfrc522Registers::tPrescaler, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25�s.
    writeRegister(mfrc522Registers::tReloadH, 0x03);		// Reload timer with 0x3E8 = 1000, 25ms before timeout.
    writeRegister(mfrc522Registers::tReloadL, 0xE8);
	
    writeRegister(mfrc522Registers::txAsk, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
    writeRegister(mfrc522Registers::mode, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363
    antennaOn(); 						// enable antenna
    setAntennaGain(0x70);				// set the antenna gain
}

void Mfrc522::antennaOn(){
    uint8_t value = readRegister(mfrc522Registers::txControl);
    writeRegister(mfrc522Registers::txControl, value |= 0x03); // set lower 2 bits
}

void Mfrc522::antennaOff(){
    uint8_t value = readRegister(mfrc522Registers::txControl);
    writeRegister(mfrc522Registers::txControl, value&0xFC); // clear lower 2 bits
}

void Mfrc522::setAntennaGain(uint8_t value){
    if(getAntennaGain() != value){
        clearRegisterBitMask(mfrc522Registers::rfcFg, (0x07<<4));
        setRegisterBitMask(mfrc522Registers::rfcFg, value & (0x07<<4));
    }
}

uint8_t Mfrc522::getAntennaGain(){
    return readRegister(mfrc522Registers::rfcFg) & (0x07 << 4);
}

Mfrc522::statusCodes Mfrc522::communicateWithTag(const mfrc522Commands command,
                                                 const uint8_t * sendData, 
                                                 const uint8_t sendDataLen,
                                                 uint8_t * receiveData,
                                                 const uint8_t receiveDataLen){
    
    writeRegister(mfrc522Registers::command, static_cast<uint8_t>(mfrc522Commands::idle));		// Stop any active command.
    writeRegister(mfrc522Registers::comIrq, 0x7F);			// Clear all seven interrupt request bits
    setRegisterBitMask(mfrc522Registers::FIFOLevel, 0x80);     // flush the buffer
    writeRegister(mfrc522Registers::FIFOData, sendData, sendDataLen);	// Write sendData to the FIFO
    writeRegister(mfrc522Registers::command, static_cast<uint8_t>(command)); //execute command
    
    if(command == mfrc522Commands::transceive){
        setRegisterBitMask(mfrc522Registers::bitFraming, 0x80); //start send
    }
    int i = 50; //max ~50 milliseconds timeout
    while(true){
        uint8_t n = readRegister(mfrc522Registers::comIrq);	
        if(n & 0x30){
            break; // Tag found
        }
        else if(n & 0x01){	
            return statusCodes::statusTimeout; // no Tag found
        }
        if(--i == 0){	
            return statusCodes::statusError; // something went wrong. Is the mfrc522 connected properly?
        }
        delay(1);
    }
    if(receiveData){ // if receiveData is not nullptr
      uint8_t recievedLen = readRegister(mfrc522Registers::FIFOLevel);
        if(receiveDataLen >= recievedLen){ // does the data fit in the given container?
            for(uint8_t i = 0;i < recievedLen;i++){
                receiveData[i] = readRegister(mfrc522Registers::FIFOData); // copy data
            }
        }
    }
    return statusCodes::statusOk;
}

bool Mfrc522::isTagPresent(){
    writeRegister(mfrc522Registers::bitFraming, 0x07);
    
    uint8_t data = static_cast<uint8_t>(mifareCommands::reqIdle); // first element is the command to send to the tag. Here we request every tag that is in idle
    
    statusCodes status = communicateWithTag(mfrc522Commands::transceive, &data, 1, nullptr, 0); // nullptr beacause we do not need ro read data from the tag.

    return status == statusCodes::statusOk;
}

Mfrcc522::statusCodes Mfrc522::receiveTagId(uint8_t * inputForId){
    writeRegister(mfrc522Registers::bitFraming, 0x07);

    uint8_t data = static_cast<uint8_t>(mifareCommands::antiColl);

    statusCodes status = communicateWithTag(mfrc522Commands::transceive, &data, 1, inputForId, 16);

    return status;
}