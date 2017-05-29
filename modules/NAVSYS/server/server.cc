/**
 * \file
 * \brief     Server side code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

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

void Server::run(){
    //Running in the nineties
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
                    broadcastMessage("Client added, so we got that going for us, which is nice");
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
    if(input == "REQUEST_GRAPH"){
        broadcastMessage("Ik ben een graaf");         //Placeholder
    }
}