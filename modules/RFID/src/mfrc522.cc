/**
 *\file
 *\author Stefan de Beer
 *\copyright Copyright (c) 2017, The R2D2 Team
 *\license See LICENSE
 */


#include "mfrc522.hh"

#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>

void Mfrc522::writeRegister(unsigned char address, unsigned char value){
    address <<= 1;
    unsigned char data[2] = {address, value}; // clearing address byte for writing
    wiringPiSPIDataRW (0, data, 2);
}

void Mfrc522::writeRegister(unsigned char address, unsigned char * value, unsigned int len){
    for(unsigned int i = 0;i<len; i++){
      writeRegister(address, value[i]);
    }
}

unsigned char Mfrc522::readRegister(unsigned char address){
    unsigned char data[2];
    data[0] = 0x80 | (address<<1); //Setting address byte for reading
    wiringPiSPIDataRW(0, data, 2);
    return data[1];
}
  
void Mfrc522::setRegisterBitMask(unsigned char address, unsigned char mask){
    unsigned char buffer = readRegister(address);
    writeRegister(address, buffer|mask);
}

void Mfrc522::clearRegisterBitMask(unsigned char address, unsigned char mask){
    unsigned char buffer = readRegister(address);
    buffer &= (~mask);
    writeRegister(address, buffer);
}

void Mfrc522::softReset(){
    writeRegister(0x01, 0x0F); //Send softReset command.
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
    writeRegister(tReloadRegH, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
    writeRegister(tReloadRegL, 0xE8);
	
    writeRegister(txAskReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
    writeRegister(modeReg, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)
    antennaOn(); 						// enable antenna
    setAntennaGain(0x70);				// set the antenna gain
}

void Mfrc522::antennaOn(){
    unsigned char value = readRegister(txControlReg);
    writeRegister(txControlReg, value |= 0x03); // set lower 2 bits
}

void Mfrc522::antennaOff(){
    unsigned char value = readRegister(txControlReg);
    writeRegister(txControlReg, value&0xFC); // clear lower 2 bits
}

void Mfrc522::setAntennaGain(unsigned char value){
    if(getAntennaGain() != value){
        clearRegisterBitMask(rfcFgReg, (0x07<<4));
	setRegisterBitMask(rfcFgReg, value & (0x07<<4));
    }
}

unsigned char Mfrc522::getAntennaGain(){
    return readRegister(rfcFgReg) & (0x07 << 4);
}

unsigned char Mfrc522::communicateWithTag(unsigned char command,
                            unsigned char * sendData, 
                            unsigned int sendDataLen,
                            unsigned char * receiveData,
                            unsigned int receiveDataLen){
    
    writeRegister(commandReg, idle);		// Stop any active command.
    writeRegister(comIrqReg, 0x7F);			// Clear all seven interrupt request bits
    setRegisterBitMask(FIFOLevelReg, 0x80);     // flush the buffer
    writeRegister(FIFODataReg, sendData, sendDataLen);	// Write sendData to the FIFO
    writeRegister(commandReg, command); 
    
    if(command == transceive){
        setRegisterBitMask(bitFramingReg, 0x80);
    }
    int i = 100000;
    while (1) {
        unsigned char n = readRegister(comIrqReg);	
        if (n & 0x30) {
            break; // Tag found
        }
        else if (n & 0x01) {	
            return statusTimeout; // no Tag found
        }
        if (--i == 0) {	
            return statusError; // something went wrong. Is the mfrc522 connected properly?
        }
    }
    if(receiveData){ // if receiveData is not NULL
        unsigned int recievedLen = readRegister(FIFOLevelReg);
        if(receiveDataLen >= recievedLen){ // does the data fit in the given container?
            std::cout<<"hi"<<std::endl;
            for(unsigned int i = 0;i < recievedLen;i++){
                receiveData[i] = readRegister(FIFODataReg); // copy data
            }
        }
    }
    return statusOk;
    
}

bool Mfrc522::isTagPresent(){
    writeRegister(bitFramingReg, 0x07);
    
    unsigned char data[1];
    data[0] = mifareReqIdle; // first element is the command to send to the tag. Here we request every tag that is in idle
    
    unsigned char status = communicateWithTag(transceive, data, 1, NULL, 0); // NULL beacause we do not need ro read data from the tag.

    if(status == statusOk){
        return 1;
    }
    return 0;
}

