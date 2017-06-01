/**
 * \file
 * \brief     Server side code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */
#include <iterator>
#include <algorithm>
#include <fstream>
#include "server.hh"

Server::Server(const uint16_t port): port(port){}

void Server::broadcastMessage(const std::string &message){
    if(!connectedClientSockets.empty()){
        sf::Packet p;
        p << message;
        for(auto &s : connectedClientSockets){
            if(s->send(p) != sf::Socket::Done){
                std::cout << "Sending message failed" << std::endl;
            }
        }
    }
}
//
void Server::run(){

    // Running in the nineties
    socketListener.listen(port);
    socketSelector.add(socketListener);


    while(true){

        sf::sleep(sf::milliseconds(100));

        if(socketSelector.wait()){

            if(socketSelector.isReady(socketListener)){
                auto client = new sf::TcpSocket;

                if(socketListener.accept(*client) == sf::Socket::Done){
                    std::cout << "New client hype" << std::endl;

                    connectedClientSockets.push_back(client);
                    socketSelector.add(*client);
                } else{
                    std::cout << "Something went wrong connecting to a new socket, please try again" << std::endl;
                    delete client;
                }

            } else{
                for(auto &s : connectedClientSockets){

                    if(socketSelector.isReady(*s)){
                        sf::Packet p;
                        std::string str;
                        if(s->receive(p) == sf::Socket::Done){
                            std::cout << "Hooray, you received a package" << std::endl;
                            p >> str;
                            std::cout << str << std::endl;
                            // This is not a nice way to do things, but there needs to be something that works
                            handleInput(str);
                        }
                    }
                }
            }
        }
    }
}

void Server::handleInput(const std::string & input){
    if(input == "REQUEST_NODES"){
        std::cout << "nodes are being send\n";
        broadcastMessage(readNodesAsString());         //Placeholder
    }
    if(input == "REQUEST_VERTICES"){
        std::cout << "vertices are  being send\n";
        broadcastMessage(readVerticesAsString());         //Placeholder
    }

}

std::string Server::readNodesAsString(){


    std::string nodeFilePath = "../server/node.txt";
    std::ifstream nodes(nodeFilePath);

    char n;
    std::string stringOfNodes = "";
    while( nodes.get(n) ){
        stringOfNodes+= n;
    }
    nodes.close();
    return stringOfNodes;


}

std::string Server::readVerticesAsString(){

    std::string verticeFilePath = "../server/vertice.txt";
    std::ifstream vertices(verticeFilePath);

    char v;
    std::string stringOfVertices = "";
    while( vertices.get(v) ){
        stringOfVertices+= v;
    }
    vertices.close();
    return stringOfVertices;

}