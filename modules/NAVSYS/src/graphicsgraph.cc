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

void graphicalfactory::draw(sf::RenderWindow & window){
for(auto it = graphicalnodes.begin(); it != graphicalnodes.end(); ++it) {
	it->draw(window);
}
	
	for(auto it = graphicalvertices.begin(); it != graphicalvertices.end(); ++it) {
	it->draw(window);
}
	
	

	std::cout << " iik print" ;
}
