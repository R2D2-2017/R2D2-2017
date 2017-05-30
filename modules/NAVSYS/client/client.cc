/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"

Client::Client(sf::IpAddress ipAddress, uint16_t port): ipAddress(ipAddress), port(port){}

void Client::run(){
	sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
	if(connectionStatus != sf::Socket::Done){
		std::cout << "Connection failed" << std::endl;
	}

	sf::Packet receivedMessage;
	std::string messageString;

	requestGraph();

	while(true){
		sf::sleep(sf::milliseconds(100));

		if(socket.receive(receivedMessage) != sf::Socket::Done){
			std::cout << "Something went wrong with receiving" << std::endl;
		} else{
			receivedMessage >> messageString;
			std::cout << messageString << std::endl;
		}
	}
}

void Client::requestGraph(){
	sf::Packet p;
	p << std::string("REQUEST_GRAPH");
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}