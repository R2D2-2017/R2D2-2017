/**
 * \file	  encryption.hh
 * \brief     Class that applies simple non safe encryption
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include <string>

class Encryption{
private:
    int encryptKey;
public:
    
    /**
     * \brief Constructor for if using your own key code.
     */
	Encryption();


	/**
	 * Contructor for if you're using fixed key
	 *
	 * \param[in]   encryptionKey   Key that will be used by the object for standard encryption
	 */
	Encryption(int encryptionKey);
    
   /**
     * \brief Can encrypt a string, with a given keycode
     * 
     * \param[in,out]   input   Input string that will be encrypted
     * \param[in]   keyCode  keyCode that will be used the encrypt the string with a specific key
     * \return Encrypted string
     */
    std::string Encrypt(std::string input, int keyCode);
    
   /**
     * \brief can encrypt a string if the encryption key is given with the constuctor
     * 
     * \param[in,out]   input   Input string that will be encrypted with a give encryption key in constructor or later set with setEncryptionKey()
     * \return Encrypted string
     */
    std::string Encrypt(std::string input);
    
    /**
     * \brief Can solve the previously encrypted string
     * 
     * \param[in,out]   input   Input string that will be decrypted
     * \param[in]   keyCode  keyCode that will be used the decrypt the string with a specific key
     * \return Returns a decrypted string if the keyCode is the same as applied in the encryption
     */
    std::string Decrypt(std::string input, int keyCode);
    
    /**
     * \brief Decrypts the previously encrypted string
     * 
     * \param[in,out]   input   Input string that will be decrypted
     * \return Returns a Decrypted string
     */
    std::string Decrypt(std::string input);
    
    /**
     * \brief Set the encryption key
     *
     * \param[in,out] Input string that will be decrypt with a give encryption key in constructor or later set with setEncryptionKey()
     */
    void setEncryptionKey(int encryptionKey);

};

