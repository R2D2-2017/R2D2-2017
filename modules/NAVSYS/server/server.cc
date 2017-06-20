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

class messageBroadcastFailed : public std::exception {
public:
    const char * what () const throw() {
        return "The message had failed to broadcast.\n";
	}
};

class messageToClientFailed : public std::exception {
public:
    const char * what () const throw() {
        return "The message had failed to send the client.\n";
	}
};

class socketConnectionFailed : public std::exception {
public:
    const char * what () const throw() {
        return "The server failed to connect to the socket.\n";
	}
};

class packageReceiveFailed : public std::exception {
public:
    const char * what () const throw() {
        return "The server failed to receive a message.\n";
	}
};

class inputHandleFailed : public std::exception {
public:
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
void Server::broadcastMessage(const command &cmd, const T & message) {
    if (!connectedClientSockets.empty()) {
        sf::Packet p;
        p << cmd << message;
        for (auto &s : connectedClientSockets) {
            if (s->send(p) != sf::Socket::Done) {
                throw messageBroadcastFailed ();
            }
        }
    }
}

template <typename T>
void Server::sendMessageToClient(sharedSocketPtr_t &client, const command &cmd, const T &message){
    sf::Packet p;
    p << cmd << message;
    if (client->send(p) != sf::Socket::Done) {
        throw messageToClientFailed ();
    }
}

void Server::run() {
    try{
        socketListener.listen(port);
        socketSelector.add(socketListener);

        while (true) {
            sf::sleep(sf::milliseconds(100));
            if (socketSelector.wait()) {
                if (socketSelector.isReady(socketListener)) {
                    sharedSocketPtr_t client = std::make_shared<sf::TcpSocket>();
                    if (socketListener.accept(*client) != sf::Socket::Done) {
                        throw socketConnectionFailed ();
                    }
                    std::cout << "Adding new client. \n";
                    connectedClientSockets.push_back(client);
                    socketSelector.add(*client);
                    std::cout << "The server has started succesfully.\n";
                } else {
                    for (auto &s : connectedClientSockets) {
                        if (socketSelector.isReady(*s)) {
                            sf::Packet p;
                            if (s->receive(p) == sf::Socket::Done) {
                                std::cout << "You have received a package. \n";
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
    } catch (const std::exception & error) {
        std::cerr << "Server exited with error: " << error.what() << '\n';
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
    } else {
        throw inputHandleFailed ();
    }

}
