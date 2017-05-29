/**
 * \file
 * \brief     A small program for showing rfid card detection
 * \author    Stefan de Beer
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "mfrc522.hh"

int main(int argc, char **argv) {
    wiringPiSetup();
    wiringPiSPISetup(0, 10000000);//max speed for mfrc522 is 10Mhz
    Mfrc522 rfid;
    rfid.init();
    while(true){
        if(rfid.isTagPresent()){
	    std::cout<<"hello tag"<<std::endl;
	}
    }
  return 0;
}
