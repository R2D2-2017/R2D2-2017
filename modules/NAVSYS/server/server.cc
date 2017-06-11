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
#include "../common/astar.hh"
#include "../common/graph-factory.hh"

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
                        
                        //command::none due to initialization warning
                        command c = command::none;
                        path nodes;
                        //std::string str;
                        if(s->receive(p) == sf::Socket::Done){
                            std::cout << "Hooray, you received a package" << std::endl;
                            p >> c >> nodes;//str
                            //std::cout << str << std::endl;
                            // This is not a nice way to do things, but there needs to be something that works
                            handleInput("", c, nodes);//str);

                        }
                    }
                }
            }
        }
    }
}


void Server::handleInput(std::string input, command c, path nodes){//const std::string & input){
    if(input == "REQUEST_NODES"){
        broadcastMessage(readNodesAsString());
    }
    if(input == "REQUEST_VERTICES"){
        broadcastMessage(readVerticesAsString());
    }
    // Request path
    if(c == command::requestPath) {//input.at(0) == 'P'){

        std::string nodeFilePath = "../server/node.txt";
        std::string verticeFilePath = "../server/vertice.txt";

        GraphFactory factory =  GraphFactory();
        Graph g = Graph();
        factory.createGraph(nodeFilePath,verticeFilePath, g);
        
        /*
        // strings to store chars parsed
        std::string nodeA = "";
        std::string nodeB = "";

        // flags to to deside based on specific chars, which data element is being read
        bool nodeFlagA = 0;
        bool nodeFlagB = 0;

        //start at index 1 because index 0 denotes the command issued
        unsigned int i = 1;
        while (i < input.length()) {
            char c = input.at(i);

            if (c == '(' && !nodeFlagB) {
                nodeFlagA = 1;
            }
            else if (c == '(' && nodeFlagB) {
                //nothing
            }
            else if (c == ')') {
                nodeFlagA = 0;
                nodeFlagB = 0;

            }
            else if (c == '-'){
                nodeFlagB =1;
            }
            else {
                if (nodeFlagA) {
                    nodeA += c;
                }
                if (nodeFlagB) {
                    nodeB += c;
                }
            }

            i++;
        }*/

        Node start( g.getNodeByName(nodes.startNode).getCoordinate().x, g.getNodeByName(nodes.startNode).getCoordinate().y, //startNode == nodeA
              g.getNodeByName(nodes.startNode).getName());

        Node end( g.getNodeByName(nodes.endNode).getCoordinate().x, g.getNodeByName(nodes.endNode).getCoordinate().y,
                      g.getNodeByName(nodes.endNode).getName());

        std::vector<PathNode> path = aStar(g, start, end);
        std::string str;
        for (auto it = path.begin(); it != path.end(); it++)
        {
            str.append(it->getName());
            if(it != path.end()-1){
                str.append(" --> ");
            }
        }

        broadcastMessage(str);

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