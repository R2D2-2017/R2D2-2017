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

    Node n1(Coordinate(0.f, 1.f), "A");
    Node n2(Coordinate(1.f, 2.f), "B");
    Node n3(Coordinate(4.f, 0.f), "C");
	Node n4(Coordinate(0.f, 2.f), "D");
	Node n5(Coordinate(5.f, 5.f), "E");
	Node n6(Coordinate(1.f, 4.f), "F");
	Node n7(Coordinate(3.f, 4.f), "G");
	Node n8(Coordinate(2.f, 3.f), "H");
	Node n9(Coordinate(5.f, 3.f), "I");
	Node n10(Coordinate(7.f, 3.f), "J");
	Node n11(Coordinate(6.f, 4.f), "K");
	Node n12(Coordinate(6.f, 2.f), "L");
	Node n13(Coordinate(.1f, 0.f), "S");

    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
	g.addNode(n4);
	g.addNode(n5);
	g.addNode(n6);
	g.addNode(n7);
	g.addNode(n8);
	g.addNode(n9);
	g.addNode(n10);
	g.addNode(n11);
	g.addNode(n12);
	g.addNode(n13);

	Vertice v1(n1, n2, 3);
	Vertice v2(n1, n4, 4);
	Vertice v3(n1, n13, 7);
	Vertice v4(n2, n1, 3);
	Vertice v5(n2, n4, 4);
	Vertice v6(n2, n8, 1);
	Vertice v7(n2, n9, 4);
	Vertice v8(n2, n13, 2);
	Vertice v9(n3, n12, 2);
	Vertice v10(n3, n13, 3);
	Vertice v11(n4, n1, 4);
	Vertice v12(n4, n2, 4);
	Vertice v13(n4, n6, 5);
	Vertice v14(n5, n7, 2);
	Vertice v15(n5, n11, 5);
	Vertice v16(n6, n4, 5);
	Vertice v17(n6, n8, 3);
	Vertice v18(n7, n5, 2);
	Vertice v19(n7, n8, 2);
	Vertice v20(n8, n2, 1);
	Vertice v21(n8, n6, 3);
	Vertice v22(n8, n7, 2);
	Vertice v23(n9, n2, 4);
	Vertice v24(n9, n10, 6);
	Vertice v25(n9, n11, 4);
	Vertice v26(n9, n12, 4);
	Vertice v27(n10, n9, 6);
	Vertice v28(n10, n11, 4);
	Vertice v29(n10, n12, 4);
	Vertice v30(n11, n5, 5);
	Vertice v31(n11, n9, 4);
	Vertice v32(n11, n10, 4);
	Vertice v33(n12, n3, 2);
	Vertice v34(n12, n9, 4);
	Vertice v35(n12, n10, 4);
	Vertice v36(n13, n1, 7);
	Vertice v37(n13, n2, 2);
	Vertice v38(n13, n3, 3);

    g.addVertice(v1);
    g.addVertice(v2);
    g.addVertice(v3);
    g.addVertice(v4);
    g.addVertice(v5);
    g.addVertice(v6);
	g.addVertice(v7);
	g.addVertice(v8);
	g.addVertice(v9);
	g.addVertice(v10);
	g.addVertice(v11);
	g.addVertice(v12);
	g.addVertice(v13);
	g.addVertice(v14);
	g.addVertice(v15);
	g.addVertice(v16);
	g.addVertice(v17);
	g.addVertice(v18);
	g.addVertice(v19);
	g.addVertice(v20);
	g.addVertice(v21);
	g.addVertice(v22);
	g.addVertice(v23);
	g.addVertice(v24);
	g.addVertice(v25);
	g.addVertice(v26);
	g.addVertice(v27);
	g.addVertice(v28);
	g.addVertice(v29);
	g.addVertice(v30);
	g.addVertice(v31);
	g.addVertice(v32);
	g.addVertice(v33);
	g.addVertice(v34);
	g.addVertice(v35);
	g.addVertice(v36);
	g.addVertice(v37);
	g.addVertice(v38);

    std::vector<PathNode> path = aStar(&g, &n13, &n5);

    std::cout << "the path is:\n";

    for (auto it = path.begin(); it != path.end(); it++)
    {
        std::cout << *it << '\n';
    }



    return 0;
}
