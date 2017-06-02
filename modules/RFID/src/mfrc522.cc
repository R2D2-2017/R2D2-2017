/**
 *\file
 *\author Stefan de Beer, Arco Gelderblom
 *\copyright Copyright (c) 2017, The R2D2 Team
 *\license See LICENSE
 */

#include "mfrc522.hh"

#include <wiringPi.h>
#include <wiringPiSPI.h>

void Mfrc522::writeRegister(uint8_t address, uint8_t value){
    address <<= 1;
    uint8_t data[2] = {address, value}; // clearing address byte for writing
    wiringPiSPIDataRW (0, data, 2);
}

void Mfrc522::writeRegister(uint8_t address, uint8_t * value, unsigned int len){
    for(uint8_t i = 0;i<len; i++){
      writeRegister(address, value[i]);
    }
}

unsigned char Mfrc522::readRegister(uint8_t address){
    uint8_t data[2];
    data[0] = 0x80 | (address<<1); //Setting address byte for reading
    wiringPiSPIDataRW(0, data, 2);
    return data[1];
}
  
void Mfrc522::setRegisterBitMask(uint8_t address, uint8_t mask){
    uint8_t buffer = readRegister(address);
    writeRegister(address, buffer|mask);
}

void Mfrc522::clearRegisterBitMask(uint8_t address, uint8_t mask){
    uint8_t buffer = readRegister(address);
    buffer &= (~mask);
    writeRegister(address, buffer);
}

void Mfrc522::softReset(){
    writeRegister(0x01, mfrcSoftReset); //Send softReset command.
    delay(50); //wait while resetting.
    while(readRegister(0x01)&(1<<4)); //wait for bit 4(powerDown bit) to clear if not reset yet.
}

void Mfrc522::init(){
    pinMode(6, OUTPUT); // The reset pin
    if(!digitalRead(6)){
        digitalWrite(6, HIGH);
        delay(50); //wait for mfrc522 to reset
    }else{
        softReset();
    }
    
    writeRegister(tModeReg, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
    writeRegister(tPrescalerReg, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25�s.
    writeRegister(tReloadRegH, 0x03);		// Reload timer with 0x3E8 = 1000, 25ms before timeout.
    writeRegister(tReloadRegL, 0xE8);
	
    writeRegister(txAskReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
    writeRegister(modeReg, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363
    antennaOn(); 						// enable antenna
    setAntennaGain(0x70);				// set the antenna gain
}

void Mfrc522::antennaOn(){
    uint8_t value = readRegister(txControlReg);
    writeRegister(txControlReg, value |= 0x03); // set lower 2 bits
}

void Mfrc522::antennaOff(){
    uint8_t value = readRegister(txControlReg);
    writeRegister(txControlReg, value&0xFC); // clear lower 2 bits
}

void Mfrc522::setAntennaGain(uint8_t value){
    if(getAntennaGain() != value){
        clearRegisterBitMask(rfcFgReg, (0x07<<4));
	setRegisterBitMask(rfcFgReg, value & (0x07<<4));
    }
}

uint8_t Mfrc522::getAntennaGain(){
    return readRegister(rfcFgReg) & (0x07 << 4);
}

Mfrc522::statusCodes Mfrc522::communicateWithTag(uint8_t command,
                            uint8_t * sendData, 
                            uint8_t sendDataLen,
                            uint8_t * receiveData,
                            uint8_t receiveDataLen){
    
    writeRegister(commandReg, idle);		// Stop any active command.
    writeRegister(comIrqReg, 0x7F);			// Clear all seven interrupt request bits
    setRegisterBitMask(FIFOLevelReg, 0x80);     // flush the buffer
    writeRegister(FIFODataReg, sendData, sendDataLen);	// Write sendData to the FIFO
    writeRegister(commandReg, command); //execute command
    
    if(command == transceive){
        setRegisterBitMask(bitFramingReg, 0x80); //start send
    }
    int i = 50; //max ~50 milliseconds timeout
    while(true){
        uint8_t n = readRegister(comIrqReg);	
        if(n & 0x30){
            break; // Tag found
        }
        else if(n & 0x01){	
            return statusTimeout; // no Tag found
        }
        if(--i == 0){	
            return statusError; // something went wrong. Is the mfrc522 connected properly?
        }
        delay(1);
    }
    if(receiveData){ // if receiveData is not nullptr
        uint8_t recievedLen = readRegister(FIFOLevelReg);
        if(receiveDataLen >= recievedLen){ // does the data fit in the given container?
            for(uint8_t i = 0;i < recievedLen;i++){
                receiveData[i] = readRegister(FIFODataReg); // copy data
            }
        }
    }
    return statusOk;
    
}

bool Mfrc522::isTagPresent(){
    writeRegister(bitFramingReg, 0x07);
    
    uint8_t data = mifareReqIdle; // first element is the command to send to the tag. Here we request every tag that is in idle
    
    statusCodes status = communicateWithTag(transceive, &data, 1, nullptr, 0); // nullptr beacause we do not need ro read data from the tag.

    if(status == statusOk){
        return true;
    }
    return false;
}
