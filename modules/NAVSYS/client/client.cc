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


    getDatabaseFromServer();

    std::string nodeFilePath = "../client/node.txt";
    std::string verticeFilePath = "../client/vertice.txt";

    GraphFactory factory =  GraphFactory();
    Graph g = Graph();
    factory.createGraph(nodeFilePath,verticeFilePath, g);
    std::cout << "graph created\n";

    //print graph to screen

    sf::Packet receivedMessage;
    std::string messageString;
    
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

void Client::getDatabaseFromServer(){

    sf::Packet receivedMessage;
    std::string messageString;

    // nodes and vertice file path
    std::string nodeFilePath = "../client/node.txt";
    std::ofstream nodeStream(nodeFilePath);

    requestNodes();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        nodeStream << messageString;
        std::cout << "nodes read\n";
    }
    nodeStream.close();

    std::string verticeFilePath = "../client/vertice.txt";
    std::ofstream verticeStream(verticeFilePath);

    requestVertices();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        verticeStream << messageString;
        std::cout << "vertices read\n";
    }

    verticeStream.close();

}


void Client::requestNodes(){
	sf::Packet p;
	p << std::string("REQUEST_NODES");
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}

void Client::requestVertices(){
	sf::Packet p;
	p << std::string("REQUEST_VERTICES");
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}
