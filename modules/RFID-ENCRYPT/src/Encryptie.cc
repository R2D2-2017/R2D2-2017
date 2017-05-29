/**
 * \file	  Encryptie.cc
 * \author    Rik Honcoop
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "Encryptie.hh"

Encryptie::Encryptie(){
    encryptKey = 1;
}

Encryptie::Encryptie(int encryptionKey){
    encryptKey = encryptionKey;
}

string Encryptie::Decrypt(string input, int keyCode){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-keyCode ;

    }
    return restr;
}

string Encryptie::Decrypt(string input){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]-encryptKey ;

    }
    return restr;
}

string Encryptie::Encrypt(string input, int keyCode){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+keyCode ;

    }
    return restr;
}

string Encryptie::Encrypt(string input){
    string restr = input;

    for(unsigned int i =0; i <= input.length() -1; i ++){
        restr[i] = restr[i]+encryptKey ;

    }
    return restr;
}

void Encryptie::setEncryptionKey(int encryptionKey){
	encryptKey = encryptionKey;
}
