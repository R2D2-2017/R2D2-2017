/**
 * \file      client.cc
 * \author    Philippe Zwietering, René de Kluis, Koen de Groot, 
 *            Arco Gelderblom, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"

#include <iostream>
#include <memory>

#include "window.hh"
#include "gestures.hh"
#include "graph-drawer.hh"
#include "../common/pathnode.hh"
#include "../common/graph-factory.hh"
#include "../common/graph-input.hh"
#include "button.hh"
#include "mouse.hh"

const int windowWidth = 800;
const int windowHeight = 480;

Client::Client(sf::IpAddress ipAddress, uint16_t port):
    ipAddress(ipAddress),
    port(port)
{}

void Client::sendPacket(sf::Packet & p) {
    if (socket.send(p) != sf::Socket::Done) {
        std::cerr << "Something went wrong while sending your message,\
                      please try again later\n";
        exit(-1);
    }
}

void Client::receivePacket(sf::Packet & p) {
    if (socket.receive(p) != sf::Socket::Done) {
        std::cerr << "Something went wrong with receiving\n";
        exit(-1);
    }
}

void Client::run(){
    sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
    if (connectionStatus != sf::Socket::Done) {
        std::cerr << "Connection failed\n";
    }
    
    getGraphFromServer();
    
    //create the window
    Window window(sf::VideoMode(windowWidth, windowHeight), "NAVSYS", 
                  sf::Style::Default);
    
    //Add a viewport
    window.setViewPort(sf::Vector2f(windowWidth, windowHeight), 
                       sf::Vector2f(100, 100));
    
    GraphDrawer drawer(window);
    
    sf::Packet receivedMessage;
    
    drawer.reload(g);
    Gestures gestureHandler(window);
    
    //Button setup
    std::vector<std::unique_ptr<Button>> buttonList;
    buttonList.push_back(std::make_unique<Button>(
                                    window, 
                                    sf::Vector2f((window.getSize().x - (buttonSize.x + 10)), 
                                     10), 
                                    buttonSize, 
                                    static_cast<int>(button::ShutDown),
                                    "shutdown"));
    buttonList.push_back(std::make_unique<Button>(
                                    window, 
                                    sf::Vector2f((window.getSize().x - (buttonSize.x + 100)),
                                                 10), 
                                    sf::Vector2f(buttonSize.x/2, buttonSize.y/2), 
                                    static_cast<int>(button::StartNode), "Start Node", 
                                    false));
    buttonList.push_back(std::make_unique<Button>(
                                    window, 
                                    sf::Vector2f((window.getSize().x - (buttonSize.x + 200)), 
                                            10), 
                                    sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2), 
                                    static_cast<int>(button::EndNode), "End Node", 
                                    false));

    bool startNodeSelected = false;
    bool endNodeSelected = false;

    sf::FloatRect startNodeButtonBounds;
    sf::FloatRect endNodeButtonBounds;

    StartEndNodeData newPath;
    clickedNode node = drawer.checkNodeClicked();
    while(true) {
        window.clear(sf::Color::Black);
        sf::sleep(sf::milliseconds(20));
        drawer.draw();
        window.setView(window.getDefaultView());
        for (auto & currButton : buttonList) {
            if (currButton->getId() == static_cast<int>(button::ShutDown)) {
                currButton->draw();
            }
            else if (currButton->getId() == static_cast<int>(button::StartNode)) {
                startNodeButtonBounds = currButton->getBounds();
                window.updateView();
                currButton->draw();
                window.setView(window.getDefaultView());
            }
            else if (currButton->getId() == static_cast<int>(button::EndNode)) {
                endNodeButtonBounds = currButton->getBounds();
                window.updateView();
                currButton->draw();
                window.setView(window.getDefaultView());
            }
            
        }
        window.updateView();
        if (GetMouseClick()) {
            for (auto & currButton : buttonList) {
                bool temp = false;
                if (currButton->isPressed()) { 
                    temp = true; 
                }
                window.setView(window.getDefaultView());
                if (currButton->isPressed()) { 
                    temp = true; 
                }
                window.updateView();
                if (temp) {
                    switch (currButton->getId()) {
                    case static_cast<int>(button::ShutDown):
                        window.close();
                        exit(0);
                        break;
                    case static_cast<int>(button::StartNode):
                        newPath.startNode = node.node->getName();
                        startNodeSelected = 1;
                        break;
                    case static_cast<int>(button::EndNode):
                        newPath.endNode = node.node->getName();
                        endNodeSelected = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
            window.updateView();
            node = drawer.checkNodeClicked();
            if (node.clicked) {
                for (auto & currButton : buttonList) {
                    window.setView(window.getDefaultView());
                    if (currButton->getId() == 
                        static_cast<int>(button::StartNode)) {
                        currButton->setPosition({
                                node.node->getBounds().left, 
                                    (node.node->getBounds().top + 
                                     1.5f*node.node->getBounds().height)});
                        currButton->setVisible(true);
                    }
                    if (currButton->getId() == static_cast<int>(button::EndNode)) {
                        currButton->setPosition({
                                 node.node->getBounds().left,
                                    (node.node->getBounds().top + 
                                     2.5f * node.node->getBounds().height)});
                        currButton->setVisible(true);
                    }
                }
                window.updateView();
            }
            else {
                for (auto & currButton : buttonList) {
                    if (currButton->getId() == 
                        static_cast<int>(button::StartNode) || 
                        currButton->getId() == 
                        static_cast<int>(button::EndNode)) {
                        currButton->setVisible(false);
                    }
                }
            }
        }
        
        window.display();
        
        if (startNodeSelected && endNodeSelected) {
            std::cout << "name of start node > " << newPath.startNode << "\n";
            drawer.setBeginNode(newPath.startNode);
            std::cout << "name of end node > " << newPath.endNode << "\n";
            drawer.setEndNode(newPath.endNode);

            requestPath(newPath);
            receivePacket(receivedMessage);
            
            std::vector<PathNode> thePath;
            command cmd = command::None;
            receivedMessage >> cmd >> thePath;
            
            if (cmd != command::ResponsePath) {
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
            startNodeSelected = 0;
            endNodeSelected = 0;
        }
        
        if (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.moveViewPort(gestureHandler.getMouseDrag(20));
            window.updateView();
        }
    }
}

void Client::getGraphFromServer() {
    sf::Packet receivedMessage;
    command commands[] = {command::RequestNodes, command::RequestVertices};
    command receivedCommand = command::None;
    
    for (const auto & cmd : commands) {
        requestGraphUsingCommand(cmd);
        receivePacket(receivedMessage);
        
        receivedMessage >> receivedCommand;
        
        if (receivedCommand == command::ResponseNodes) {
            std::vector<Node> nodes;
            receivedMessage >> nodes;
            for (const auto node : nodes) {
                g.addNode(node);
            }
        }
        else if (receivedCommand == command::ResponseVertices) {
            std::vector<Vertice> vertices;
            receivedMessage >> vertices;
            for (const auto vertice : vertices) {
                g.addVertice(vertice);
            }
        }
    }
}

void Client::requestGraphUsingCommand(const command &cmd) {
    sf::Packet p;
    p << cmd;  
    sendPacket(p);
}

void Client::requestPath(const StartEndNodeData &nodes) {
    sf::Packet p;
    p << command::RequestPath << nodes;
    sendPacket(p);
}
