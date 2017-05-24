/**
 * \file
 * \brief     INSERT A DESCRIPTION HERE
 * \author    INSERT YOUR NAME HERE
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <iostream>
#include "astar.hh"

int main(int argc, char **argv)
{
    Graph g;

    Node n1(Coordinate(5.f, 5.f));
    Node n2(Coordinate(10.f, 10.f));
    Node n3(Coordinate(5.f, 10.f));

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);

    Vertice v1(n1, n2, 5);
    Vertice v2(n2, n1, 5);
    Vertice v3(n2, n3, 4);
    Vertice v4(n3, n2, 4);
    Vertice v5(n1, n3, 2);
    Vertice v6(n3, n1, 2);

    g.addVertice(v1);
    g.addVertice(v2);
    g.addVertice(v3);
    g.addVertice(v4);
    g.addVertice(v5);
    g.addVertice(v6);

    std::vector<std::shared_ptr<PathNode>> path = Astar(&g, &n1, &n2);

    std::cout << "the path is:\n";

    for (auto it = path.begin(); it != path.end(); it++)
    {
        std::cout << it->get()->getCoordinate() << '\n';
    }

    return 0;
}
