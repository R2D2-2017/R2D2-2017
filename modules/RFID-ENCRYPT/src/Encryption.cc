/**
 * \file	  Encryption.cc
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "Encryption.hh"

Encryption::Encryption(){
encryptKey = 1;
}

Encryption::Encryption(int encryptionKey){
encryptKey = encryptionKey;
}

string Encryption::Decrypt(string input, int keyCode){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-keyCode ;

    }
    return restr;
}

string Encryption::Decrypt(string input){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-encryptKey ;

    }
    return restr;
}

string Encryption::Encrypt(string input, int keyCode){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+keyCode ;

    }
    return restr;
}

string Encryption::Encrypt(string input){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+encryptKey ;

    }
    return restr;
}

void Encryption::setEncryptionKey(int encryptionKey){
	encryptKey = encryptionKey;
}
