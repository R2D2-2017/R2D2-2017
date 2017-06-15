/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering, René de Kluis, Koen de Groot, Arco Gelderblom, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"

#include <iostream>

#include "window.hh"
#include "gestures.hh"
#include "../common/pathnode.hh"
#include "graph-drawer.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480

Client::Client(sf::IpAddress ipAddress, uint16_t port):
    ipAddress(ipAddress),
    port(port)
{}

void Client::sendPacket(sf::Packet & p) {
    if (socket.send(p) != sf::Socket::Done) {
        std::cout << "Something went wrong while sending your message, please try again later\n";
        exit(-1);
    }
}

void Client::checkPacketCorrectlyReceived(sf::Packet & p) {;
    if (socket.receive(p) != sf::Socket::Done) {
        std::cout << "Something went wrong with receiving\n";
        exit(-1);
    }
}

void Client::run(){
    sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
    if (connectionStatus != sf::Socket::Done) {
        std::cout << "Connection failed\n";
    }
    
    getDatabaseFromServer();
    
    //create the window
    Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NAVSYS", sf::Style::Default);

    //Add a viewport
    window.setViewPort(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Vector2f(100, 100));

    GraphDrawer drawer(window);

    sf::Packet receivedMessage;

    std::string messageString;

    drawer.reload(&g);

    Gestures gestureHandler(window);
    
	//Button setup
    std::vector<Button*> buttonList;
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 10)), 10 }, { buttonSize }, static_cast<int>(button::ShutDown), "Shut Down"));
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 100)), 10 }, { buttonSize.x/2, buttonSize.y/2 }, static_cast<int>(button::StartNode), "Start Node", false));
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 200)), 10 }, { buttonSize.x / 2, buttonSize.y / 2 }, static_cast<int>(button::EndNode), "End Node", false));

    bool startNodeSelected = 0;
    bool endNodeSelected = 0;

    StartEndNodeData newPath;
    GraphNode clickedNode = drawer.checkNodeClicked();
    while(true){
        window.clear(sf::Color::Black);
        sf::sleep(sf::milliseconds(100));

        if (GetMouseClick()) {
            for (auto & indexer : buttonList) {
                if (indexer->isPressed()) {
                    switch (indexer->getId()) {
                    case static_cast<int>(button::ShutDown):
                        window.close();
                        exit(0);
                    case static_cast<int>(button::StartNode) :
                        newPath.startNode = clickedNode.getName();
                        startNodeSelected = 1;
                        break;
                    case static_cast<int>(button::EndNode) :
                        newPath.endNode = clickedNode.getName();
                        endNodeSelected = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
            clickedNode = drawer.checkNodeClicked();
            if (clickedNode.isPressed(window)) {
                for (auto & indexer : buttonList) {
                    if (indexer->getId() == static_cast<int>(button::StartNode)) {
                        indexer->setPosition({ 
                            clickedNode.getBounds().left, 
                            clickedNode.getBounds().top + 1.5f*clickedNode.getBounds().height }
                        );
                        indexer->setVisable(true);
                    }
                    if (indexer->getId() == static_cast<int>(button::EndNode)) {
                        indexer->setPosition({ 
                            clickedNode.getBounds().left, 
                            clickedNode.getBounds().top + 2.5f* clickedNode.getBounds().height }
                        );
                        indexer->setVisable(true);
                    }
                }
            }
            else {
                for (auto & indexer : buttonList) {
                    if (
                        indexer->getId() == static_cast<int>(button::StartNode) || 
                        indexer->getId() == static_cast<int>(button::EndNode)) {
                            indexer->setVisable(false);
                    }
                }
            }
        }

        for (auto & indexer : buttonList) {
            indexer->draw();
        }

        drawer.draw(); 

        if(startNodeSelected && endNodeSelected) {
            std::cout << "name of start node > " << newPath.startNode << "\n";
            drawer.setBeginNode(newPath.startNode);
            std::cout << "name of end node > " << newPath.endNode << "\n";
            drawer.setEndNode(newPath.endNode);

            requestPath(newPath);
            checkPacketCorrectlyReceived(receivedMessage);
            
            std::vector<PathNode> thePath;
            command cmd = command::none;
            receivedMessage >> cmd >> thePath;
            
            if (cmd != command::responsePath) {
                std::cout << "Incorrect response from server\n";
            }
            else {
                std::cout << "The path is: ";

                for (unsigned int i = 0; i < thePath.size()-1; i++) {
                    std::cout << thePath[i].getName() << " --> ";
                }
                std::cout << thePath.back().getName() << "\n\n";
            }
            drawer.highlightPath(thePath);
            std::cout<<"Press Escape to clear this path and insert a new path\n";
            while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){}
            drawer.reload(&g);
            startNodeSelected = 0;
            endNodeSelected = 0;
        }
        if( window.isOpen()) {
            sf::Event event;
            while( window.pollEvent(event) ){
                if( event.type == sf::Event::Closed ){
                    window.close();
                }
            }
            window.moveViewPort(gestureHandler.getMouseDrag(20));
            window.updateView();
        }
    }
}

void Client::getDatabaseFromServer() {
    sf::Packet receivedMessage;
    command commands[] = {command::requestNodes, command::requestVertices};
    command receivedCommand = command::none;
    
    for (const auto & cmd : commands) {
        requestDatabaseUsingCommand(cmd);
        checkPacketCorrectlyReceived(receivedMessage);
        
        receivedMessage >> receivedCommand;
        
        if (receivedCommand == command::responseNodes) {
            std::vector<Node> nodes;
            receivedMessage >> nodes;
            for (const auto node : nodes) {
                g.addNode(node);
            }
        }
        else if (receivedCommand == command::responseVertices) {
            std::vector<Vertice> vertices;
            receivedMessage >> vertices;
            for (const auto vertice : vertices) {
                g.addVertice(vertice);
            }
        }
    }
}

void Client::requestDatabaseUsingCommand(const command & cmd) {
    sf::Packet p;
    p << cmd;  
    sendPacket(p);
}

void Client::requestPath(StartEndNodeData nodes) {
    sf::Packet p;
    p << command::requestPath << nodes;
    sendPacket(p);
}

void Client::buttonAction(sf::RenderWindow & window, int buttonId, GraphNode clickedNode) {
    switch (buttonId) {
    case static_cast<int>(button::ShutDown):
        window.close();
        exit(0);
    case static_cast<int>(button::StartNode) :
        std::cout << clickedNode.getName();
        break;
    case static_cast<int>(button::EndNode) :
        std::cout << clickedNode.getName();
        break;
    default:
        break;
    }
}
