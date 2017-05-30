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

    // nodes and vertice file path
    std::string nodeFilePath = "../server/node.txt";
    std::string verticeFilePath = "../server/vertice.txt";


    //graph factory
    std::cout << "Creating graph" << std::endl;
    GraphFactory factory = GraphFactory();
    Graph g = Graph();
    factory.createGraph(nodeFilePath,verticeFilePath, g);
    std::cout << "Initializing listener" << std::endl;
    //Running in the nineties
    socketListener.listen(port);
    socketSelector.add(socketListener);
    std::cout << "Running service" << std::endl;
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
        std::cout << "graph is being send\n";
        broadcastMessage("Ik ben een graaf");         //Placeholder
    }
    else if(input == "ADD_NODE"){
        std::cout << "node is being added to \n";
        broadcastMessage("Node added");         //Placeholder
    }
    else if(input == "ADD_VERTICE"){
        std::cout << "graph is being send\n";
        broadcastMessage("Vertice added");         //Placeholder
    }
    else if(input == "SAVE_GRAPH"){
        std::cout << "graph is being saved\n";
        broadcastMessage("graph saved");         //Placeholder
    }

}