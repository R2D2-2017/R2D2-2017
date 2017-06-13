
/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering, Arco Gelderblom, Tim IJntema
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"
#include "pathnode.hh"


Client::Client(sf::IpAddress ipAddress, uint16_t port): ipAddress(ipAddress), port(port){}

void Client::sendPacket(sf::Packet & p) {
    if(socket.send(p) != sf::Socket::Done){
        std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
        exit(-1);
    }
}

void Client::checkPacketCorrectlyReceived(sf::Packet & p) {;
    if(  socket.receive(p) != sf::Socket::Done  ){
        std::cout << "Something went wrong with receiving" << std::endl;
        exit(-1);
    }
}

void Client::run(){
    sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
    if(connectionStatus != sf::Socket::Done){
        std::cout << "Connection failed" << std::endl;
    }
    
    // this loads the the files declared above with the database
    getDatabaseFromServer();
    
    //create the window
    sf::RenderWindow  window{ sf::VideoMode{ 1000, 1000}, "NAVSYS" };
    GraphDrawer drawer(window);

    sf::Packet receivedMessage;

    //used to let the user know a knew request can be made
    bool printOptionsFlag =1;
    while(true){
        window.clear(sf::Color::Black);
		sf::sleep(sf::milliseconds(100));

        drawer.reload(&g);
        drawer.draw();

        if(printOptionsFlag){
            printOptionsFlag = 0;
            std::cout << "press Left to enter route information\n";
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            StartEndNodeData newPath;
            std::cout << "name of start node>";
            std::cin >> newPath.startNode;
            drawer.setBeginNode(newPath.startNode);
            std::cout << "name of end node>";
            std::cin >> newPath.endNode;
            drawer.setEndNode(newPath.endNode);

            requestPath(newPath);
            checkPacketCorrectlyReceived(receivedMessage);
            
            std::vector<PathNode> thePath;
            command cmd = command::none;
            receivedMessage >> cmd >> thePath;
                
            if (cmd != command::responsePath){
                std::cout << "Incorrect response from server\n";
            }
            else {
                std::cout << "The path is: ";
                for (unsigned int i = 0; i < thePath.size()-1; i++) {
                    std::cout << thePath[i].getName() << " --> ";
                }
                std::cout << thePath.back().getName() << "\n\n";
            }

            //used to let the user know a knew request can be made
            printOptionsFlag = 1;
        }

        if( window.isOpen()) {
            	sf::Event event;
            	while( window.pollEvent(event) ){
                    if( event.type == sf::Event::Closed ){
                        window.close();
                    }
                }
        }
    }
}


void Client::getDatabaseFromServer() {
    sf::Packet receivedMessage;
    command commands[] = {command::requestNodes, command::requestVertices};
    command receivedCommand = command::none;
    
    for (auto cmd : commands) {
        requestDatabaseUsingCommand(cmd);
        checkPacketCorrectlyReceived(receivedMessage);
        
        receivedMessage >> receivedCommand;
        
        if (receivedCommand == command::responseNodes) {
            std::vector<Node> nodes;
            receivedMessage >> nodes;
            for (const auto node : nodes){
                g.addNode(node);
            }
        }
        else if (receivedCommand == command::responseVertices) {
            std::vector<Vertice> vertices;
            receivedMessage >> vertices;
            for (const auto vertice : vertices){
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

void Client::requestPath(StartEndNodeData nodes){
    sf::Packet p;
    p << command::requestPath << nodes;
    sendPacket(p);
}

