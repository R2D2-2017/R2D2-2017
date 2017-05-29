/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"

Client::Client(const sf::IpAddress ipAddress, uint16_t port): ipAddress(ipAddress), port(port){}

void Client::run(){
	connectionStatus = socket.connect(ipAddress, port);
	if(connectionStatus != sf::Socket::Done){
		std::cout << "Connection failed" << std::endl;
	}

	sf::Packet receivedMessage;

	while(true){
		sf::sleep(sf::milliseconds(100));

		if(socket.receive(receivedMessage) != sf::Socket::Done){
			std::cout << "Something went wrong with receiving" << std::endl;
		} else{
			std::cout << receivedMessage << std::endl;
		}
	}

}