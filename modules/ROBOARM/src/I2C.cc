/**
 * \file
 * \author    Matthijs Vos
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
 #include "I2C.hh"

I2C::I2C(hwlib::i2c_bus &i2c_bus):
	
 	// reset();
 	// setPWMFreq(1000);

i2c_bus(i2c_bus)
{
}
// I2C::~I2C(){
// 	// delete i2c_bus;
// }

void I2C::reset(){
	sendCommand(0x00,0x00);//Normal mode
	sendCommand(0x01,0x04);//totem pole
}

//! Set the frequency of PWM
/*!
 \param freq desired frequency. 40Hz to 1000Hz using internal 25MHz oscillator.
 */
void I2C::setPWMFreq(int freq){
	uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;
	sendCommand(MODE1,0x10);//sleep
	sendCommand(PRE_SCALE,prescale_val);//multiplyer for PWM frequency
	sendCommand(MODE1,0x80);//restart
	sendCommand(MODE2,0x04);//totem pole
}

//! PWM a single channel
/*!
 \param led channel (1-16) to set PWM value for
 \param value 0-4095 value for PWM
 */
void I2C::setPWM(uint8_t led,int value){
	setPWM(led,0,value);
}
//! PWM a single channel with custom on time
/*!
 \param led channel (1-16) to set PWM value for
 \param on_value 0-4095 value to turn on the pulse
 \param off_value 0-4095 value to turn off the pulse
 */
 void I2C::setPWM(uint8_t led,int on_value, int off_value){
 	sendCommand(LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF);
 	sendCommand(LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8);
 	sendCommand(LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF);
 	sendCommand(LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8);
 	

 }

 void I2C::moveServoTo(uint8_t servo,int degrease){
	 static const int min = 4095 / 100 * 4;
	 static const int max = 4095 / 100 * 14;

	 setPWM(servo, min + ((max - min) / 180) * degrease);
 }

 //! Get current PWM value
/*!
 \param led channel (1-16) to get PWM value from, not working yet
 */
 int I2C::getPWM(uint8_t led){
 	int ledval = 0;
 // 		ledval = i2c_bus.read(0x40,LED0_OFF_H + LED_MULTIPLYER * (led-1));
	// ledval = ledval & 0xf;
	// ledval <<= 8;
	// ledval += i2c_bus.read(0x40,LED0_OFF_L + LED_MULTIPLYER * (led-1));
	return ledval;
 }
void I2C::runDemo(){
//Doesnt work with current test

 // 	hwlib::cout << "Test" << "\r\n";
 //    // Sends a series of commands to the extender, the first command will 
 //    // set the GPIO pins as out, the second command sets the pins high, 
 //    // followed by a wait  of 500ms for test purposes 
 //    // Set commands will be added when the new extender arrives
	// uint8_t prescale_val = (CLOCK_FREQ / 4096 / 60  - 1);
	// sendCommand(MODE1, 0x10); //sleep
	// hwlib::cout << "Running Demo" << "\r\n";
	// sendCommand(PRE_SCALE, prescale_val); // multiplyer for PWM frequency
	// hwlib::cout << "Running Demo" << "\r\n";
	// sendCommand(MODE1, 0x80); //restart
	// sendCommand(MODE2, 0x04); //totem pole (default)
	// unsigned int on_value = 409;
	// hwlib::cout << "Running Demo" << "\r\n";
	// unsigned int off_value = 1228;
	// //sendCommand(0x2F, on_value & 0xFF);
	// //sendCommand(0x2E, on_value >> 8 &0xF);
	// sendCommand(0x2F, 0);
	// hwlib::cout << "Running Demo" << "\r\n";
	// sendCommand(0x30, off_value & 0xFF);
	// sendCommand(0x31, off_value >> 8 &0xF);


}
void I2C::sendCommand(uint8_t registerAdress,uint8_t registerValues){

	 // Currently fixed value because this is the only slave at this iteration
	uint8_t slaveAdress = 0x40;
	
	const uint8_t command[size] ={registerAdress,registerValues};
	// // Writes the command to the slaveAdress, pointing to a certain register and sets a byte there
	i2c_bus.write(slaveAdress,command,2);
}
