/**
 *\file
 *\brief Mfrc522 library is a library for interfacing with the Mfrc522 module
 *\author Stefan de Beer
 *\copyright Copyright (c) 2017, The R2D2 Team
 *\license See LICENSE
 */

#pragma once

#include <stdint.h>

class Mfrc522{
public:
  
    /**
     *\brief An Enum for commands that an rfid tag can execute. the commands can be send to the rfid tag.
     */ 
    enum mifareCommands{
        mifareReqAll    = 0x52,
        mifareReqIdle   = 0x26,
        mifareAntiColl  = 0x93,
        mifareSelect    = 0x93,
        mifareAuthen    = 0x60,
        mifareRead      = 0x30,
        mifareWrite     = 0xA0,
        mifareDecr      = 0xC0,
        mifareIncr      = 0xC1,
        mifareRest      = 0xC2,
        mifareTrans     = 0xB0,
        mifareHalt      = 0x50
    };
    
    /**
     * \brief An enum for various commands. these commands can be written to the lower 4 bits of register commandReg to be executed.
     */
    enum mfrc522Commands{
        idle            = 0x00, /**No action, cancels current command execution.*/
        Mem             = 0x01, /**Stores 25 bytes into internal buffer.*/
        genRandomId     = 0x02, /**Generates a 10-byte random ID number.*/
        calcCrc         = 0x03, /**Activates the CRC coprocessor or performs a self test.*/
        Transmit        = 0x04, /**Transmit data from the FIFO buffer.*/
        noCmdChange     = 0x07, /**No command change, can be used for modifing CommandReg without affecting the command.*/
        receive         = 0x08, /**Activates the receiver circuits.*/
        transceive      = 0x0C, /**Transmit data from FIFO buffer to antenna and activate reiver after tranmission.*/
        mfAuthent       = 0x0E, /**Performs the MIFARE standard authentication.*/
        mfrcSoftReset   = 0x0F  /**Resets the mfrc522.*/       
    };
    
    /**
     * \brief An enum for various types of tags with their hex value.
     */
    enum PICC_Type {
	PICC_TYPE_UNKNOWN	= 0,
	PICC_TYPE_ISO_14443_4	= 1,	/** PICC compliant with ISO/IEC 14443-4*/ 
	PICC_TYPE_ISO_18092	= 2, 	/** PICC compliant with ISO/IEC 18092 (NFC)*/
	PICC_TYPE_MIFARE_MINI	= 3,	/** MIFARE Classic protocol, 320 bytes*/
	PICC_TYPE_MIFARE_1K	= 4,	/** MIFARE Classic protocol, 1KB*/
	PICC_TYPE_MIFARE_4K	= 5,	/** MIFARE Classic protocol, 4KB*/
	PICC_TYPE_MIFARE_UL	= 6,	/** MIFARE Ultralight or Ultralight C*/
	PICC_TYPE_MIFARE_PLUS	= 7,	/** MIFARE Plus*/
	PICC_TYPE_TNP3XXX	= 8,	/** Only mentioned in NXP AN 10833 MIFARE Type Identification Procedure*/
	PICC_TYPE_NOT_COMPLETE	= 255	/** SAK indicates UID is not complete.*/
    };
    
    /**
     * \brief An enum for all unreserved registers in the mfrc522.
     */
    enum mfrc522Registers{
        commandReg		= 0x01,	/** starts and stops command execution*/
        comIEnReg		= 0x02,	/** enable and disable interrupt request control bits*/
	divIEnReg		= 0x03,	/** enable and disable interrupt request control bits*/
	comIrqReg		= 0x04,	/** interrupt request bits*/
	divIrqReg		= 0x05,	/** interrupt request bits*/
	errorReg		= 0x06,	/**error bits showing the error status of the last command executed*/ 
	status1Reg		= 0x07,	/** communication status bits*/
	status2Reg		= 0x08,	/** receiver and transmitter status bits*/
	FIFODataReg             = 0x09,	/** input and output of 64 byte FIFO buffer*/
	FIFOLevelReg            = 0x0A,	/** number of bytes stored in the FIFO buffer*/
	waterLevelReg           = 0x0B,	/** level for FIFO underflow and overflow warning*/
	controlReg		= 0x0C,	/** miscellaneous control registers*/
	bitFramingReg           = 0x0D,	/** adjustments for bit-oriented frames*/
	collReg			= 0x0E,	/** bit position of the first bit-collision detected on the RF interface*/

	modeReg			= 0x11,	/** defines general modes for transmitting and receiving */
	txModeReg		= 0x12,	/**defines transmission data rate and framing*/
	rxModeReg		= 0x13,	/** defines reception data rate and framing*/
	txControlReg            = 0x14,	/** controls the logical behavior of the antenna driver pins TX1 and TX2*/
	txAskReg		= 0x15,	/** controls the setting of the transmission modulation*/
	txSelReg		= 0x16,	/** selects the internal sources for the antenna driver*/
	rxSelReg		= 0x17,	/** selects internal receiver settings*/
	rxThresholdReg          = 0x18,	/** selects thresholds for the bit decoder*/
	demodReg		= 0x19,	/** defines demodulator settings*/
	mfTxReg			= 0x1C,	/** controls some MIFARE communication transmit parameters*/
	mfRxReg			= 0x1D,	/** controls some MIFARE communication receive parameters*/
	serialSpeedReg          = 0x1F,	/** selects the speed of the serial UART interface*/

	crcResultRegH           = 0x21,	/** shows the MSB and LSB values of the CRC calculation*/
	crcResultRegL           = 0x22,
	modWidthReg		= 0x24,	/** controls the ModWidth setting*/
	rfcFgReg		= 0x26,	/** configures the receiver gain*/
	gsNReg			= 0x27,	/** selects the conductance of the antenna driver pins TX1 and TX2 for modulation */
	cwGsPReg		= 0x28,	/** defines the conductance of the p-driver output during periods of no modulation*/
	modGsPReg		= 0x29,	/** defines the conductance of the p-driver output during periods of modulation*/
	tModeReg		= 0x2A,	/** defines settings for the internal timer*/
	tPrescalerReg           = 0x2B,	/** the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.*/
	tReloadRegH		= 0x2C,	/** defines the 16-bit timer reload value*/
	tReloadRegL		= 0x2D,
	tCounterValueRegH       = 0x2E,	/** shows the 16-bit timer value*/
	tCounterValueRegL       = 0x2F,
	
        testSel1Reg             = 0x31,	/** general test signal configuration*/
	testSel2Reg		= 0x32,	/** general test signal configuration*/
	testPinEnReg            = 0x33,	/** enables pin output driver on pins D1 to D7*/
	testPinValueReg         = 0x34,	/** defines the values for D1 to D7 when it is used as an I/O bus*/
	testBusReg              = 0x35,	/** shows the status of the internal test bus*/
	autoTestReg		= 0x36,	/** controls the digital self test*/
	versionReg		= 0x37,	/** shows the software version*/
	analogTestReg           = 0x38,	/** controls the pins AUX1 and AUX2*/
	testDAC1Reg		= 0x39,	/** defines the test value for TestDAC1*/
	testDAC2Reg		= 0x3A,	/** defines the test value for TestDAC2*/
	testADCReg		= 0x3B  /** shows the value of ADC I and Q channels*/
    };
    
    enum statusCodes{
        statusOk = 0x00,
        statusError = 0x01,
        statusTimeout = 0x02
        
    };
    
    /**
     * \brief A function for writing an unsigned char to an address in the mfrc522.
     * \param address The address in the mfrc522 value should be written to.
     * \param value The value to be written to the mfrc522 register
     */
    void writeRegister(unsigned char address, unsigned char value);
    
    void writeRegister(unsigned char address, unsigned char * value, unsigned int len);
    
    /**
     * \brief A function for reading an unsigned char from a register in the mfrc522.
     * \param address The address the data should be read from.
     * \return Returns an unsigned char read from the mfrc522. 
     */
    unsigned char readRegister(unsigned char address);
    
    /**
     * \brief A function for setting only the selected bits
     * @param address The address in the mfrc522 the mask should be written to.
     * @param mask The Mask that should be written to the register.
     */
    void setRegisterBitMask(unsigned char address, unsigned char mask);
    
    /**
     * \brief A function for clearing the selected bits.
     * @param address The address in the mfrc522 the mask should be written to.
     * @param mask The Mask that should be written to the register.
     */
    void clearRegisterBitMask(unsigned char address, unsigned char mask);
    
    /**
     * \brief A function for performing a software reset.
     */
    void softReset();
    
    /**
     * \brief A function for initializing the mfrc522.
     */
    void init();
    
    /**
     * \brief A function for enabling the antennas
     */
    void antennaOn();
    
    /**
     * \brief A function for disabling the antennas
     */
    void antennaOff();
    
    /**
     * \brief A function for setting the antenna gain
     * @param value The antenna gain to be set. Possible values can be found in the mfrc522 datasheet at page 59.
     */
    void setAntennaGain(unsigned char value);
    
    /**
     * \brief A function for getting the antenna gain
     * @return The antenna gain
     */
    unsigned char getAntennaGain();
    
    /**
     * \brief A function for communicating with an rfid tag.
     * @param command The command to be executed. e.g. transceive
     * @param sendData The data to be send to the tag. The first element should be the command the tag should execute
     * @param sendDataLen The size of sendData
     * @param receiveData A container for storing the data received from the tag in
     * @param receiveDataLen The size of receiveData
     * @return The function return a status code. statusOk for succes, statusTimeout if no tag was found or a statusError if something else went wrong
     */
    unsigned char communicateWithTag(unsigned char command,
                       unsigned char * sendData, 
                       unsigned int sendDataLen,
                       unsigned char * receiveData,
                       unsigned int receiveDataLen);
    
    /**
     * \brief A function for checking if there is a tag that can be communicated with.
     * @return Returns true if a tag was found, false if no tag was found.
     */
    bool isTagPresent();
};



