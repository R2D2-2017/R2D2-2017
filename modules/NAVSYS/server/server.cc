/**
 * \file
 * \brief     Server side code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "server.hh"
#include <iterator>
#include <algorithm>
#include "../common/astar.hh"

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
        for(auto &s : connectedClientSockets){
            if(s->send(p) != sf::Socket::Done){
                std::cout << "Sending message failed" << std::endl;
                exit(-1);
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
                uniqueSocket_t client;

                if(socketListener.accept(*client) != sf::Socket::Done){
                    std::cout << "Something went wrong connecting to a new socket, please try again" << std::endl;
                }
                
                std::cout << "New client hype" << std::endl;
                connectedClientSockets.push_back(client);
                socketSelector.add(*client);

            } else{
                for(auto &s : connectedClientSockets){
                    if(socketSelector.isReady(*s)){
                        sf::Packet p;
                        
                        if(s->receive(p) == sf::Socket::Done){
                            std::cout << "Hooray, you received a package" << std::endl;
                            
                            handleInput(p);

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
        
//        /broadcastMessage(command::responsePath, path);

    }

}