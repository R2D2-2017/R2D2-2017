/**
 * \file
 * \brief     Server side code for the NAVSYS API
 * \author    Philippe Zwietering, Amrit Malhi
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "server.hh"
#include <iostream>
#include "astar.hh"

struct messageBroadcastFailed : public std::exception {
  const char * what () const throw() {
	   return "The message had failed to send.\n";
	}
};

struct socketConnectionFailed : public std::exception {
  const char * what () const throw() {
	   return "The server failed to connect to the socket.\n";
	}
};

struct packageReceiveFailed : public std::exception {
  const char * what () const throw() {
	   return "The server failed to receive a message.\n";
	}
};

struct inputHandleFailed : public std::exception {
  const char * what () const throw() {
	   return "The server failed to handle the input.\n";
	}
};

Server::Server(const uint16_t port):
    port(port)
{
    std::string nodeFilePath = "../server/node.txt";
    std::string verticeFilePath = "../server/vertice.txt";

    GraphFactory factory;
    factory.createGraph(nodeFilePath,verticeFilePath, g);
}

template <typename T>
void Server::broadcastMessage(const command &cmd, const T & message){
    if(!connectedClientSockets.empty()){
        sf::Packet p;
        p << cmd << message;
        for(auto &s : connectedClientSockets) {
            if(s->send(p) != sf::Socket::Done) {
                throw messageBroadcastFailed ();
            }
        }
    }
}

void Server::run(){
    socketListener.listen(port);
    socketSelector.add(socketListener);

    while(true){

        sf::sleep(sf::milliseconds(100));

        if(socketSelector.wait()){
            if(socketSelector.isReady(socketListener)){
                sharedSocketPtr_t client = std::make_shared<sf::TcpSocket>();
                if(socketListener.accept(*client) != sf::Socket::Done){
                    throw socketConnectionFailed ();
                }

                std::cout << "Adding new client." << std::endl;
                connectedClientSockets.push_back(client);
                socketSelector.add(*client);
                std::cout << "The server has started succesfully.\n";
            } else {
                for(auto &s : connectedClientSockets){
                    if(socketSelector.isReady(*s)){
                        sf::Packet p;

                        if(s->receive(p) == sf::Socket::Done){
                            std::cout << "You have received a package." << std::endl;
                            handleInput(p);

                        }
                        else {
                          throw packageReceiveFailed ();
                        }
                    }
                }
            }
        }
    }
}


void Server::handleInput(sf::Packet & p){
    //command::none due to initialization warning
    command cmd = command::none;
    p >> cmd;

    if(cmd == command::requestNodes) {
        broadcastMessage(command::responseNodes, g.getNodes());
    }
    else if(cmd == command::requestVertices) {
        broadcastMessage(command::responseVertices, g.getVertices());
    }
    else if(cmd == command::requestPath) {
        StartEndNodeData pathToFind;
        p >> pathToFind;

        Node start( g.getNodeByName(pathToFind.startNode) );
        Node end( g.getNodeByName(pathToFind.endNode) );
        std::vector<PathNode> path = aStar(g, start, end);
        broadcastMessage(command::responsePath, path);
    }
    else {
        throw inputHandleFailed ();
    }
}
