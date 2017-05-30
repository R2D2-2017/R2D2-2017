#include "graphicsgraph.hh" 

graphicalfactory::graphicalfactory(Graph * g):
	g(g)
	{
		std::vector<Node> nodevector = g->getNodes();	
		for(auto it = nodevector.begin(); it != nodevector.end(); ++it) {
	   		graphicalnodes.push_back(graphnodes(sf::Vector2f(it->getCoordinate().x*100,it->getCoordinate().y*100)));
		}
		std::vector<Vertice> verticevector = g->getVertices();	
		for(auto it = verticevector.begin(); it != verticevector.end(); ++it) {
			graphicalvertices.push_back(vertices(sf::Vector2f(it->getCurrent()->getCoordinate().x*100,it->getCurrent()->getCoordinate().y*100),sf::Vector2f(it->getNeighbour()->getCoordinate().x*100,it->getNeighbour()->getCoordinate().y*100)));     
		}

	}

void graphicalfactory::draw(){	
	window.clear();
	for(auto it = graphicalnodes.begin(); it != graphicalnodes.end(); ++it) {
		it->draw(window);
	}
	for(auto it = graphicalvertices.begin(); it != graphicalvertices.end(); ++it) {
		it->draw(window);
	}
while (window.isOpen()) {
			
				window.display();
				sf::sleep( sf::milliseconds( 60 ));
				sf::Event event;
				while( window.pollEvent(event) ){
					if( event.type == sf::Event::Closed ){
						window.close();
					}
				}
			}
}

