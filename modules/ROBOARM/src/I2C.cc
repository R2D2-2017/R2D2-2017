/**
 * \file
 * \author    Matthijs Vos
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 #include "I2C.hh"
	
I2C::I2C(hwlib::i2c_bus &i2c_bus):
i2c_bus(i2c_bus)
{
}

void I2C::runDemo(){


 	hwlib::cout << "Running Demo" << "\r\n";
    // Sends a series of commands to the extender, the first command will 
    // set the GPIO pins as out, the second command sets the pins high, 
    // followed by a wait  of 500ms for test purposes 
    // Set commands will be added when the new extender arrives
 	sendCommand(0x00,0x00);
 	sendCommand(0x12,0xFF);

    hwlib::wait_ms(500);
    sendCommand(0x12,0x00);

}
void I2C::sendCommand(uint8_t registerAdress,uint8_t registerValues){

	// Currently fixed value because this is the only slave at this iteration
	uint8_t slaveAdress = 0x20;
	
	const uint8_t command[size] ={registerAdress,registerValues};
	// Writes the command to the slaveAdress, pointing to a certain register and sets a byte there
	i2c_bus.write(slaveAdress,command,2);
}
