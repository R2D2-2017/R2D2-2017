
/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering, Arco Gelderblom
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"


Client::Client(sf::IpAddress ipAddress, uint16_t port): ipAddress(ipAddress), port(port){}



void Client::run(){
	sf::Socket::Status connectionStatus = socket.connect(ipAddress, port);
	if(connectionStatus != sf::Socket::Done){
		std::cout << "Connection failed" << std::endl;
	}


    std::string nodeFilePath = "../client/node.txt";
    std::string verticeFilePath = "../client/vertice.txt";
    // this loads the the files declared above with the database
    getDatabaseFromServer(nodeFilePath,verticeFilePath);

    //create the graph
    GraphFactory factory =  GraphFactory();
    Graph g = Graph();
    factory.createGraph(nodeFilePath,verticeFilePath, g);

    //create the window
    sf::RenderWindow  window{ sf::VideoMode{ 1000, 1000}, "NAVSYS" };
    GraphDrawer drawer(window);


    sf::Packet receivedMessage;
    std::string messageString;

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
            std::string startNode;
            std::string endNode;
            std::cout << "name of start node>";
            std::cin >> startNode;
            drawer.setBeginNode(startNode);
            std::cout << "name of end node>";
            std::cin >> endNode;
            drawer.setEndNode(endNode);
            sf::sleep(sf::seconds(2));
            requestPath(startNode, endNode);

            if(  socket.receive(receivedMessage) != sf::Socket::Done  ){
                std::cout << "Something went wrong with receiving" << std::endl;
            }
            else{
                receivedMessage >> messageString;
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


void Client::getDatabaseFromServer(std::string nodeFilePath, std::string verticeFilePath){

    sf::Packet receivedMessage;
    std::string messageString;

    std::ofstream nodeStream(nodeFilePath);

    requestNodes();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        nodeStream << messageString;
    }
    std::cout<<messageString;
    nodeStream.close();

    std::ofstream verticeStream(verticeFilePath);

    requestVertices();

    if(socket.receive(receivedMessage) != sf::Socket::Done){
        std::cout << "Something went wrong with receiving" << std::endl;
    }
    else{
        receivedMessage >> messageString;
        verticeStream << messageString;
    }

    verticeStream.close();

}


void Client::requestNodes(){
	sf::Packet p;
	p << std::string("REQUEST_NODES");
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}


void Client::requestVertices(){
	sf::Packet p;
	p << std::string("REQUEST_VERTICES");
	if(socket.send(p) != sf::Socket::Done){
		std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
	}
}

void Client::requestPath(std::string startNode, std::string endNode){
    sf::Packet p;
    std::string str;
    str.append("P(");
    str.append(startNode);
    str.append(")-(");
    str.append(endNode);
    str.append(")");
    p << str;
    if(socket.send(p) != sf::Socket::Done){
        std::cout << "Something went wrong while sending your message, please try again later" << std::endl;
    }
}

