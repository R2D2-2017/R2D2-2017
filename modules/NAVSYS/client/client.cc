
/**
 * \file
 * \brief     Client side connection code for the NAVSYS API
 * \author    Philippe Zwietering, René de Kluis, Koen de Groot
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "client.hh"


Client::Client(sf::IpAddress ipAddress, uint16_t port): 
    ipAddress(ipAddress), 
    port(port)
{}



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
    sf::RenderWindow  window{ sf::VideoMode{ 1500, 1000}, "SFML window", sf::Style::Fullscreen };
    GraphDrawer printOnScreen(window);


    sf::Packet receivedMessage;
    std::string messageString;

    printOnScreen.reload(&g);

	//Button setup
    std::vector<Button*> buttonList;
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 10)), 10 }, { buttonSize }, static_cast<int>(button::ShutDown), "Shut Down"));
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 100)), 10 }, { buttonSize.x/2, buttonSize.y/2 }, static_cast<int>(button::StartNode), "Start Node", false));
    buttonList.push_back(new Button(window, { float(window.getSize().x - (buttonSize.x + 200)), 10 }, { buttonSize.x / 2, buttonSize.y / 2 }, static_cast<int>(button::EndNode), "End Node", false));


    //used to let the user know a knew request can be made
    bool printOptionsFlag =1;
    GraphNode clickedNode = printOnScreen.checkNodeClicked();
	while(true){
        window.clear(sf::Color::Black);
		sf::sleep(sf::milliseconds(10));

        if (GetMouseClick()) {
            for (auto & indexer : buttonList) {
                if (indexer->isPressed()) {
                    buttonAction(window, indexer->getId(), clickedNode);
                }
            }
            clickedNode = printOnScreen.checkNodeClicked();
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
        
        printOnScreen.draw();
        for (auto & indexer : buttonList) {
            indexer->draw();
        }
        window.display();


        if(printOptionsFlag){
            printOptionsFlag = 0;
            std::cout << "Press Left to enter route information\n";
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            std::string startNode;
            std::string endNode;
            std::cout << "Name of start node>";
            std::cin >> startNode;
            std::cout << "Name of end node>";
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

void Client::buttonAction(sf::RenderWindow & window, int buttonId, GraphNode clickedNode) {
    switch (buttonId) {
    case static_cast<int>(button::ShutDown):
        window.close();
        exit(1);
        break;
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

