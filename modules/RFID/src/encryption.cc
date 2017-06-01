/**
 * \file	  encryption.cc
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "encryption.hh"

Encryption::Encryption(){
encryptKey = 1;
}

Encryption::Encryption(int encryptionKey){
encryptKey = encryptionKey;
}

std::string Encryption::Decrypt(std::string input, int keyCode){
    std::string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-keyCode ;

    }
    return restr;
}

std::string Encryption::Decrypt(std::string input){
    std::string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-encryptKey ;

    }
    return restr;
}

std::string Encryption::Encrypt(std::string input, int keyCode){
    std::string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+keyCode ;

    }
    return restr;
}

std::string Encryption::Encrypt(std::string input){
    std::string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+encryptKey ;

    }
    return restr;
}

void Encryption::setEncryptionKey(int encryptionKey){
	encryptKey = encryptionKey;
}
