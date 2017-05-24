/**
 * \file
 * \brief     Server side code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "server.hh"

Server::Server(const uint16_t port): port(port){
    socketListener.listen(port);
    socketSelector.add(socketListener);
}

void Server::broadcastMessage(const std::string &message){
    if(!connectedClientSockets.empty()){
        sf::Packet p;
        p << message;
        for(auto &s : connectedClientSockets){
            if(s->send(p) != sf::Socket::Done){
                std::cout << "Doomptiedoo you done goofed, sending broadcast failed" << std::endl;
            }
        }
    }
}

void Server::run(){
    //Running in the nineties
    while(true){
        if(socketSelector.wait()){

            if(socketSelector.isReady(socketListener)){
                auto client = std::make_shared<sf::TcpSocket>(sf::TcpSocket());

                if(socketListener.accept(*client) == sf::Socket::Done){
                    connectedClientSockets.push_back(client);
                    socketSelector.add(*client);
                } else{
                    std::cout << "Something went wrong connecting to a new socket, please try again" << std::endl;
                }

            } else{
                for(auto &s : connectedClientSockets){
                    if(socketSelector.isReady(*s)){
                        sf::Packet p;
                        if(s->receive(p) == sf::Socket::Done){
                            std::cout << "Hooray, you received a package" << std::endl;
                            std::cout << p << std::endl;
                            // HandleInput will be called here usually, not set up yet, cause I dont know what everything is gonna be doing in the end
                        }
                    }
                }
            }
        }
    }
}

void Server::killEveryLittleThingIsGonnaBeAlright(){
    socketSelector.clear();
    socketListener.close();
    if(!connectedClientSockets.empty()){
        for(auto &s : connectedClientSockets){
            s->disconnect();
        }
    }
}

void Server::handleInput(){
    //Im doing nothing and im proud of it
    bool handledInput = true;
    if(handledInput){
        std::cout << "Ye we handled some input alright" << std::endl;
    }
}