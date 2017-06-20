/**
 * \file      client.cc
 * \author    Philippe Zwietering, René de Kluis, Koen de Groot,
 *            Arco Gelderblom, Tim IJntema, Rik Honcoop
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
#include "mouse.hh"

class receiveMessageFailed : public std::exception {
public:
    const char * what () const throw() {	
		return "Something went wrong with receiving a message\n";
	}
};

class sendMessageFailed : public std::exception {
public:
    const char * what () const throw() {
		return "Something went wrong with sending your message\n";
	}
};

Client::Client(sf::IpAddress ipAddress, uint16_t port):
    ipAddress(ipAddress),
    port(port)
{}

Client::~Client(){
    sf::Packet p;
    p << command::RequestDisconnect;
    sendPacket(p);
    
    receivePacket(p);
    command cmd = command::None;
    p >> cmd;
    if (cmd == command::ResponseDisconnect) {
        std::cout << "Client correctly disconnected\n";
    }
    else {
        std::cerr << "Client not disconnected\n";
    }
}

void Client::sendPacket(sf::Packet & p) {
    if (socket.send(p) != sf::Socket::Done) {
        throw sendMessageFailed() ;
    }
}

void Client::receivePacket(sf::Packet & p) {
    if (socket.receive(p) != sf::Socket::Done) {      
        throw receiveMessageFailed() ;
    }
}

void Client::connectToServer(){
		socket.disconnect();
        socket.connect(ipAddress, port);
}

bool Client::checkIfNodesCanBeStartNode(std::vector<GraphNode> nodes, std::vector<GraphVertice> vertices, std::string nodeName){
	bool checkbool =false;
	for(GraphNode & tempNode : nodes){
	    if(tempNode.getName() == nodeName){
            for(GraphVertice & tempVert : vertices){
                if(tempNode.getRealPositionX() == tempVert.getRealPositionAX() && tempNode.getRealPositionY() == tempVert.getRealPositionAY()){
			        checkbool = true;
				}
		    }				
		}
			//std::cout << temp.getName() << " " << temp.getRealPositionX() << " " << temp.getRealPositionX() << " \n";
	}
	return checkbool;
}

bool Client::checkIfNodesCanBeEndNode(std::vector<GraphNode> nodes, std::vector<GraphVertice> vertices, std::string nodeName){
    bool checkbool =false;
	for(GraphNode & tempNode : nodes){
	    if(tempNode.getName() == nodeName){
            for(GraphVertice & tempVert : vertices){
                if(tempNode.getRealPositionX() == tempVert.getRealPositionBX() && tempNode.getRealPositionY() == tempVert.getRealPositionBY()){
			        checkbool = true;
				}
		    }				
		}
			//std::cout << temp.getName() << " " << temp.getRealPositionX() << " " << temp.getRealPositionX() << " \n";
	}
	return checkbool;	    
}

void Client::run(){
    
    // Get available VideoModes
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

    // Store highest resolution VideoMode available
    sf::VideoMode fullscreenVideoMode = modes[1];

    // Create the window
    Window window(fullscreenVideoMode, "NAVSYS", sf::Style::Fullscreen);

    // Add viewport
    window.setViewPort(sf::Vector2f(fullscreenVideoMode.width, 
    fullscreenVideoMode.height), sf::Vector2f(100,100));


    MessageBox messageBox(window, { 0,0 });

    //create the window
    sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
    if (connectionStatus != sf::Socket::Done) {
        messageBox.setMessage("Connection FAILED\n");
    }

    getGraphFromServer();

    
    GraphDrawer printOnScreen(window);

    GraphDrawer drawer(window);

    sf::Packet receivedMessage;

    drawer.reload(g);
    Gestures gestureHandler(window);
    
    //Button setup
    std::vector<std::unique_ptr<Button>> buttonList;
    buttonList.push_back(std::unique_ptr<Button>(new Button(
                                    window, 
                                    {float(window.getSize().x - (buttonSize.x + 10)), 
                                            10}, 
                                    {buttonSize}, 
                                    buttonCommand::ShutDown, "Shut Down")));

    buttonList.push_back(std::unique_ptr<Button>(new Button(
                                    window,
                                    {float(window.getSize().x - (buttonSize.x + 100)),
                                            10}, 
                                    {buttonSize.x/2, buttonSize.y/2}, 
                                    buttonCommand::StartNode, "Start Node", 
                                    false)));
    buttonList.push_back(std::unique_ptr<Button>(new Button(
                                                            window, 
                                                            {float(window.getSize().x - (buttonSize.x + 200)), 
                                                                    10}, 
                                                            {buttonSize.x / 2, buttonSize.y / 2}, 
                                                            buttonCommand::EndNode, "End Node", 
                                                            false)));
    bool startNodeSelected = false;
    bool endNodeSelected = false;

    sf::FloatRect startNodeButtonBounds;
    sf::FloatRect endNodeButtonBounds;
    StartEndNodeData newPath;
    clickedNode node = drawer.checkNodeClicked();
    while(true) {
        try {
            // if getRemotePort = 0, no connention with socket / server.
            if (socket.getRemotePort() == 0) {
                socket.disconnect();
                socket.connect(ipAddress, port);
            }
            window.clear(sf::Color::Black);
            //sf::sleep(sf::milliseconds(20));
            drawer.draw();
            window.setView(window.getDefaultView());
            messageBox.draw();
            for (auto & currButton : buttonList) {
                if (currButton->getId() == buttonCommand::ShutDown) {
                    currButton->draw();
                }
                else if (currButton->getId() == buttonCommand::StartNode) {
                    startNodeButtonBounds = currButton->getBounds();
                    window.updateView();
                    currButton->draw();
                    window.setView(window.getDefaultView());
                }
                else if (currButton->getId() == buttonCommand::EndNode) {
                    endNodeButtonBounds = currButton->getBounds();

                    window.updateView();
                    currButton->draw();
                    window.setView(window.getDefaultView());
                }
            }
            window.updateView();
            if (GetMouseClick()) {
                for (auto & currButton : buttonList) {
                    drawer.reload(g);
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
                        case buttonCommand::ShutDown:
                            window.clear();
                            window.setView(window.getDefaultView());
                            messageBox.setMessage( "Shutting Down" );
                            messageBox.draw();
                            window.display();
                            sf::sleep(sf::milliseconds(1000));
                            window.close();
                            exit(0);
                            break;

                        case buttonCommand::StartNode:
                            messageBox.setMessage(("Selected: " + node.node->getName() + " as start."));
                            newPath.startNode = node.node->getName();
                            startNodeSelected = 1;
                            break;
                        case buttonCommand::EndNode:
                            messageBox.setMessage(("Selected: " + node.node->getName() + " as end."));
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
							buttonCommand::StartNode) {
							currButton->setPosition({
									node.node->getBounds().left, 
										(node.node->getBounds().top + 
										 3.f*node.node->getBounds().height)});
							currButton->setVisable(true);
						}
						if (currButton->getId() == buttonCommand::EndNode) {
							currButton->setPosition({
									node.node->getBounds().left,
										(node.node->getBounds().top + 
										 5.f * node.node->getBounds().height)});
							currButton->setVisable(true);
						}
					}
					window.updateView();
				}
				else {
					for (auto & currButton : buttonList) {
						if (currButton->getId() == 
							buttonCommand::StartNode || 
							currButton->getId() == 
							buttonCommand::EndNode) {
							currButton->setVisable(false);
						}
					}
				}
			}

			window.display();

			if(startNodeSelected && endNodeSelected && !checkIfNodesCanBeStartNode(drawer.getGraphNode(), drawer.getGraphVertice(), newPath.startNode)){
				messageBox.setMessage("Start node can not be used. because it has no connection to the grid \n");
				endNodeSelected =false;
				startNodeSelected = false;
			}else if(startNodeSelected && endNodeSelected && !checkIfNodesCanBeEndNode(drawer.getGraphNode(), drawer.getGraphVertice(), newPath.endNode)){
				messageBox.setMessage("End node can not be used. because it has no connection to the grid \n");
				endNodeSelected =false;
				startNodeSelected = false;
		
			}else if(startNodeSelected && endNodeSelected && newPath.startNode == newPath.endNode) {
				messageBox.setMessage("Start and end node cannot be the same, you are at the endpoint \n");
				endNodeSelected =false;
				startNodeSelected = false;
			
			}else if(startNodeSelected && endNodeSelected && newPath.startNode != newPath.endNode) {
				messageBox.setMessage(("Calculating Path: " + newPath.startNode + " to " + newPath.endNode));
				drawer.setBeginNode(newPath.startNode);
				drawer.setEndNode(newPath.endNode);
				messageBox.draw();
				requestPath(newPath);
				receivePacket(receivedMessage);

				std::vector<PathNode> thePath;
				command cmd = command::None;
				receivedMessage >> cmd >> thePath;

				if (cmd != command::ResponsePath) {
					messageBox.setMessage("Incorrect response from server");
					messageBox.draw();
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
				window.moveViewPort(gestureHandler.getMouseDrag(20, 150));
				window.updateView();
			}
		}
		catch (receiveMessageFailed & e) {
			std::cout << e.what() << "\n";
			startNodeSelected = false;
			endNodeSelected = false;

        }
		catch (sendMessageFailed & e) {
			std::cout << e.what() << "\n";
			startNodeSelected = false;
			endNodeSelected = false;
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
