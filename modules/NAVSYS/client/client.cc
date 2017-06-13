
/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"
#include "window.hh"
#include "gestures.hh"

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
    Window window(sf::VideoMode(1000, 1000), "NAVSYS");
    window.setViewPort(sf::Vector2f(1000, 1000), sf::Vector2f(500, 500));

    GraphDrawer printOnScreen(window);

    sf::Packet receivedMessage;
    std::string messageString;

    //used to let the user know a knew request can be made
    bool printOptionsFlag =1;

    Gestures gestureHandler(window);

	while(true){
        window.clear(sf::Color::Black);
		//sf::sleep(sf::milliseconds(16));
        printOnScreen.reload(&g);
        printOnScreen.draw();


        if(printOptionsFlag){
            printOptionsFlag = 0;
            std::cout << "press Left to enter route information\n";
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            std::string startNode;
            std::string endNode;
            std::cout << "name of start node>";
            std::cin >> startNode;
            std::cout << "name of end node>";
            std::cin >> endNode;

            requestPath(startNode, endNode);

            if(  socket.receive(receivedMessage) != sf::Socket::Done  ){
                std::cout << "Something went wrong with receiving" << std::endl;
            }
            else{
                receivedMessage >> messageString;
                std::cout << messageString << std::endl;

            }

            //used to let the user know a knew request can be made
            printOptionsFlag = 1;
        }
        //std::cout<<"hi "<< mousePos.x << ' ' << mousePos.y <<'\n';
        if( window.isOpen()) {
            sf::Event event;
            while( window.pollEvent(event) ){
                if( event.type == sf::Event::Closed ){
                    window.close();
                }
            }
            window.moveViewPort(gestureHandler.getMouseDrag(20));
            window.updateView();
            /*
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
                if(clock.getElapsedTime().asMilliseconds()>20){
                    clock.restart();
                    sf::Vector2i distance = mousePos - sf::Mouse::getPosition(window); 
                    mousePos = sf::Mouse::getPosition(window);
                    window.moveViewPort(distance);
                    window.updateView();
                }
            }else{
                mousePos = sf::Mouse::getPosition(window);
            } 
            */
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

