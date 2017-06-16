/**
 * \file      server.cc
 * \author    Philippe Zwietering, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "server.hh"
#include <iostream>
#include "astar.hh"
#include "../common/graph-factory.hh"

Server::Server(const uint16_t port):
    port(port)
{
    std::string nodeFilePath = "../server/node.txt";
    std::string verticeFilePath = "../server/vertice.txt";
    GraphFactory factory;
    factory.createGraph(nodeFilePath,verticeFilePath, g);
    
    Node start(g.getNodeByName("S"));
        Node end(g.getNodeByName("J"));
        (void)aStar(g, start, end);
}

template <typename T>
void Server::broadcastMessage(const command &cmd, const T & message) {
    if (!connectedClientSockets.empty()) {
        sf::Packet p;
        p << cmd << message;
        for (auto &s : connectedClientSockets) { 
            if (s->send(p) != sf::Socket::Done) {
                std::cout << "Sending message failed\n";
                exit(-1);
            }
        }
    }
}

template <typename T>
void Server::sendMessageToClient(sharedSocketPtr_t &client, const command &cmd, const T &message){
    sf::Packet p;
    p << cmd << message;
    if (client->send(p) != sf::Socket::Done) {
        std::cout << "Sending message failed\n";
        exit(-1);
    }
}

void Server::run() {
    socketListener.listen(port);
    socketSelector.add(socketListener);
    
    while(true) {

        sf::sleep(sf::milliseconds(100));

        if (socketSelector.wait()) {
            if (socketSelector.isReady(socketListener)) {
                sharedSocketPtr_t client = std::make_shared<sf::TcpSocket>();
                if (socketListener.accept(*client) != sf::Socket::Done) {
                    std::cout << "Something went wrong connecting to a new\
                                  socket, please try again\n";
                    exit(-1);
                }
                
                std::cout << "New client hype" << std::endl;
                connectedClientSockets.push_back(client);
                socketSelector.add(*client);

            } else {
                for (auto &s : connectedClientSockets) {
                    if (socketSelector.isReady(*s)) {
                        sf::Packet p;
                        
                        if (s->receive(p) == sf::Socket::Done) {
                            std::cout << "Hooray, you received a package\n";
                            
                            handleInput(p, s);

                        }
                    }
                }
                if (!disconnectClients.empty()) {
                    for (const auto & disconnectedClient : disconnectClients){
                        connectedClientSockets.erase(
                            std::find(
                                connectedClientSockets.begin(),
                                connectedClientSockets.end(),
                                disconnectedClient));
                    }
                    disconnectClients.clear();
                }
            }
        }
    }
}


void Server::handleInput(sf::Packet & p, sharedSocketPtr_t & client) {
    //command::none due to initialization warning
    command cmd = command::None;
    p >> cmd;
    
    if (cmd == command::RequestNodes) {
        sendMessageToClient(client, command::ResponseNodes, g.getNodes());
    }
    else if (cmd == command::RequestVertices) {
        sendMessageToClient(client, command::ResponseVertices, g.getVertices());
    }
    else if (cmd == command::RequestPath) {
        StartEndNodeData pathToFind;
        p >> pathToFind;
        
        Node start(g.getNodeByName(pathToFind.startNode));
        Node end(g.getNodeByName(pathToFind.endNode));
        std::vector<PathNode> path = aStar(g, start, end);
        sendMessageToClient(client, command::ResponsePath, path);
    }
    else if (cmd == command::RequestDisconnect) {
        //disconnect client
        disconnectClients.push_back(client);
        sendMessageToClient(client, command::ResponseDisconnect, "You have been succesfully disconnected");
    }
}
