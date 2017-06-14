#ifndef MFRC522HACK_H
#define MFRC522HACK_H

//#include <Arduino.h>
#include "MFRC522.hh"
#include "MFRC522Debug.hh"

class MFRC522Hack {
private:
	MFRC522 *const _device;
public:
	MFRC522Hack(MFRC522 *const device) : _device(device) {};
	
	bool MIFARE_OpenUidBackdoor(const bool logErrors) const;
	
	bool MIFARE_SetUid(const byte *newUid, const byte uidSize, const bool logErrors) const;
	
	bool MIFARE_UnbrickUidSector(const bool logErrors) const;
};


#endif //MFRC522HACK_H
