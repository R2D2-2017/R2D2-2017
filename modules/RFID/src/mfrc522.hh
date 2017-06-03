/**
 *\file
 *\brief Mfrc522 library is a library for interfacing with the Mfrc522 module
 *\author Stefan de Beer, Arco Gelderblom
 *\copyright Copyright (c) 2017, The R2D2 Team
 *\license See LICENSE
 */

#pragma once

#include <cstdint>

/**
 *\brief This library is for interfacing with the mfrc522.
 */

class Mfrc522{
public:
  
    /**
     *\brief An Enum for commands that an rfid tag can execute. the commands can be send to the rfid tag. 
	 *These commands can be used with function communicateWithTag and should be placed in the first element of the sendData parameter. 
	 *The other element should contain the arguments to the command. After the command is executed by the rfid card, the rfid card will give a response.
     */ 
    enum class mifareCommands{
        reqAll    = 0x52, /** Request all tag in idle. argument=none, response=tag type*/
        reqIdle   = 0x26, /** Request all tags in state idle. argument=none, response=tag type*/
        antiColl  = 0x93, /** Get UID from all tags for anticollision. argument=(optional part of tags UID), response = (rest of)UID*/
        select    = 0x93, /** Select a RFID tag in range of reader. argument=UID, responce=answer to select*/
        authen    = 0x60, /** Authenticate RFID tag. argument=block address, response=acknowledge*/
        read      = 0x30, /** Read one memory block. argument=block address, respons=16 bytes of data*/
        write     = 0xA0, /** Write one memory blovk. argument=block address and 16 byte of data, response=acknowledge*/
        decrement = 0xC0, /** Decrements the contents of a block and stores the result in the internal Transfer Buffer. argument=block address and 4 byte value, response=acknowledge*/
        increment = 0xC1, /** Increments the contents of a block and stores the result in the internal Transfer Buffer. argument=block address and 4 byte value, response=acknowledge*/
        restore   = 0xC2, /** Reads the contents of a block into the internal Transfer Buffer. argument=block address and 4 byte dummy, response=acknowledge*/
        transfer  = 0xB0, /** Writes the contents of the internal Transfer Buffer to a block. argument=block address, response=acknowledge*/
        halt      = 0x50  /** Send selected tag into halt mode. argument=dummy address, repsonse=None*/
    };
    
    /**
     * \brief An enum for various commands. these commands can be written to the lower 4 bits of the register commandReg to be executed.
     */
    enum class mfrc522Commands{
        idle          = 0x00, /**No action, cancels current command execution.*/
        mem           = 0x01, /**Stores 25 bytes into internal buffer.*/
        genRandomId   = 0x02, /**Generates a 10-byte random ID number.*/
        calcCrc       = 0x03, /**Activates the CRC coprocessor or performs a self test.*/
        transmit      = 0x04, /**Transmit data from the FIFO buffer.*/
        noCmdChange   = 0x07, /**No command change, can be used for modifing CommandReg without affecting the command.*/
        receive       = 0x08, /**Activates the receiver circuits.*/
        transceive    = 0x0C, /**Transmit data from FIFO buffer to antenna and activate reiver after tranmission.*/
        mfAuthent     = 0x0E, /**Performs the MIFARE standard authentication.*/
        softReset     = 0x0F  /**Resets the mfrc522.*/       
    };
    
    /**
     * \brief An enum for various types of tags with their hex value.
     */
    enum class PICC_Type : uint8_t {
        unkown	    = 0,
	    mifareMini	= 3,	/** MIFARE Classic protocol, 320 bytes*/
	    mifare1K	= 4,	/** MIFARE Classic protocol, 1KB*/
	    mifare4K	= 5,	/** MIFARE Classic protocol, 4KB*/
	    mifareUl	= 6,	/** MIFARE Ultralight or Ultralight C*/
	    mifarePlus	= 7,	/** MIFARE Plus*/
    };
    
    /**
     * \brief An enum for all unreserved registers in the mfrc522.
     */
    enum class mfrc522Registers : uint8_t{
        command	        = 0x01,	/** starts and stops command execution*/
        comIEn          = 0x02,	/** enable and disable interrupt request control bits*/
        divIEn          = 0x03,	/** enable and disable interrupt request control bits*/
        comIrq  	    = 0x04,	/** interrupt request bits*/
        divIrq          = 0x05,	/** interrupt request bits*/
        error           = 0x06,	/**error bits showing the error status of the last command executed*/ 
        status1         = 0x07,	/** communication status bits*/
        status2		    = 0x08,	/** receiver and transmitter status bits*/
        FIFOData        = 0x09,	/** input and output of 64 byte FIFO buffer*/
        FIFOLevel       = 0x0A,	/** number of bytes stored in the FIFO buffer*/
        waterLevel      = 0x0B,	/** level for FIFO underflow and overflow warning*/
        control         = 0x0C,	/** miscellaneous control registers*/
        bitFraming      = 0x0D,	/** adjustments for bit-oriented frames*/
        coll            = 0x0E,	/** bit position of the first bit-collision detected on the RF interface*/

        mode            = 0x11,	/** defines general modes for transmitting and receiving */
        txMode		    = 0x12,	/**defines transmission data rate and framing*/
        rxMode		    = 0x13,	/** defines reception data rate and framing*/
        txControl       = 0x14,	/** controls the logical behavior of the antenna driver pins TX1 and TX2*/
        txAsk		    = 0x15,	/** controls the setting of the transmission modulation*/
        txSel		    = 0x16,	/** selects the internal sources for the antenna driver*/
        rxSel		    = 0x17,	/** selects internal receiver settings*/
        rxThreshold     = 0x18,	/** selects thresholds for the bit decoder*/
        demod           = 0x19,	/** defines demodulator settings*/
        mfTx            = 0x1C,	/** controls some MIFARE communication transmit parameters*/
        mfRx            = 0x1D,	/** controls some MIFARE communication receive parameters*/
        serialSpeed     = 0x1F,	/** selects the speed of the serial UART interface*/

        crcResultH      = 0x21,	/** shows the MSB and LSB values of the CRC calculation*/
        crcResultL      = 0x22,
        modWidth        = 0x24,	/** controls the ModWidth setting*/
        rfcFg           = 0x26,	/** configures the receiver gain*/
        gsNReg          = 0x27,	/** selects the conductance of the antenna driver pins TX1 and TX2 for modulation */
        cwGsP           = 0x28,	/** defines the conductance of the p-driver output during periods of no modulation*/
        modGsP          = 0x29,	/** defines the conductance of the p-driver output during periods of modulation*/
        tMode           = 0x2A,	/** defines settings for the internal timer*/
        tPrescaler      = 0x2B,	/** the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.*/
        tReloadH        = 0x2C,	/** defines the 16-bit timer reload value*/
        tReloadL        = 0x2D,
        tCounterValue   = 0x2E,	/** shows the 16-bit timer value*/
        tCounterValueL  = 0x2F,
	
        testSel1        = 0x31,	/** general test signal configuration*/
        testSel2        = 0x32,	/** general test signal configuration*/
        testPinEn       = 0x33,	/** enables pin output driver on pins D1 to D7*/
        testPinValue    = 0x34,	/** defines the values for D1 to D7 when it is used as an I/O bus*/
        testBus         = 0x35,	/** shows the status of the internal test bus*/
        autoTest        = 0x36,	/** controls the digital self test*/
        version         = 0x37,	/** shows the software version*/
        analogTest      = 0x38,	/** controls the pins AUX1 and AUX2*/
        testDAC1        = 0x39,	/** defines the test value for TestDAC1*/
        testDAC2        = 0x3A,	/** defines the test value for TestDAC2*/
        testADC         = 0x3B  /** shows the value of ADC I and Q channels*/
    };
    /**
	 * \brief This is an enum containing various return codes used in this library.
	 */
    enum class statusCodes : uint8_t{
        statusOk      = 0x00, /** No errors */
        statusError   = 0x01, /** An error occurred */
        statusTimeout = 0x02 /** connection to tag timed out */
        
    };
    
    /**
     * \brief A function for writing an unsigned char to an address in the mfrc522.
     * \param[in] address The address in the mfrc522 value should be written to.
     * \param[in] value The value to be written to the mfrc522 register
     */
    void writeRegister(mfrc522Registers reg, uint8_t value);

    /**
     *\brief A function for writing multiple bytes to the mfrc522
     *\param[in] address The address of the register in the mfrc522 to write the bytes to.
     *\param[in] value The array of data to be written to the mfrc522.
     *\param[in] len The length of the data to be written.
     */
    void writeRegister(mfrc522Registers reg, uint8_t * value, unsigned int len);
    
    /**
     * \brief A function for reading an unsigned char from a register in the mfrc522.
     * \param[in] address The address the data should be read from.
     * \return Returns an unsigned char read from the mfrc522. 
     */
    uint8_t readRegister(mfrc522Registers reg);
    
    /**
     * \brief A function for setting only the selected bits
     * \param[in] address The address in the mfrc522 the mask should be written to.
     * \param[in] mask The Mask that should be written to the register.
     */
    void setRegisterBitMask(mfrc522Registers reg, uint8_t mask);
    
    /**
     * \brief A function for clearing the selected bits.
     * \param[in] address The address in the mfrc522 the mask should be written to.
     * \param[in] mask The Mask that should be written to the register.
     */
    void clearRegisterBitMask(mfrc522Registers reg, uint8_t mask);
    
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
     * \param[in] value The antenna gain to be set. Possible values can be found in the mfrc522 datasheet at page 59.
     */
    void setAntennaGain(uint8_t value);
    
    /**
     * \brief A function for getting the antenna gain
     * \return The antenna gain
     */
    unsigned char getAntennaGain();
    
    /**
     * \brief A function for communicating with an rfid tag.
     * \param[in] command The command to be executed. e.g. transceive
     * \param[in] sendData The data to be send to the tag. The first element should be the command the tag should execute
     * \param[in] sendDataLen The size of sendData
     * \param[out] receiveData A container for storing the data received from the tag
     * \param[in] receiveDataLen The size of receiveData
     * \return The function returns a status code. statusOk for succes, statusTimeout if no tag was found or a statusError if something else went wrong
     */
    statusCodes communicateWithTag(mfrc522Commands command,
                       uint8_t * sendData, 
                       uint8_t sendDataLen,
                       uint8_t * receiveData,
                       uint8_t receiveDataLen);
    
    /**
     * \brief A function for checking if there is a tag that can be communicated with.
     * \return Returns true if a tag was found, false if no tag was found.
     */
    bool isTagPresent();
};
