//
// Created by jeremy on 22-5-17.
//
//===-- StorageManager.cc - StorageManager class implementation -------*- C++ -*-===//
//
//                     The storageManager
//

//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the implementations of the StorageManager class, which is the
/// class that handles all IO in regards to a graph.
///
//===----------------------------------------------------------------------===//

#include "StorageManager.hh"


///author jeremy
///
/// \param nodeFilePath
/// \param verticeFilePath
///
/// The constructor for a graph storagemanager
///
StorageMngr::StorageMngr(const std::string nodeFilePath, const std::string verticeFilePath):
    nodeFilePath(nodeFilePath), verticeFilePath(verticeFilePath){

}

///author jeremy
///
/// \param tmp
/// This function sets the pointer to a graph in the storagemanager.
///
/// Output graph ptr is set.
void StorageMngr::storageSetGraph(Graph * tmp) {
    graph = tmp;

}

///author jeremy
///
/// This function closes all files opened by the Storagemanager.
///
/// This function does noot close the FILE* used for the storage of the entire graph.
/// This function is only used to close the input file streams used by the factory functions.
///
/// Output files are closed
void StorageMngr::closeFiles() {
    if (nodeFileStreamIn.is_open()){
        nodeFileStreamIn.close();
    }
    if (verticeFileStreamIn.is_open()){
        verticeFileStreamIn.close();
    }

}

///author jeremy
///
/// This function stores every node and vertice found in the graph to their respective files
/// by taking the neccesarry data and composing this to a formatted string. This string is then writed to the files.
/// This functions handles the opening and closing of the file descriptor itself.

/// Output graph is saved on disk.
void StorageMngr::storeGraphOnDisk() {
    cout<< "saving graph on disk\n";
    closeFiles();

    FILE* nodeFile;
    nodeFile = fopen(nodeFilePath.c_str(),"w");

    for_each (graph->getNodes().begin(), graph->getNodes().end(), [nodeFile](Node node){
        std::string tmp = "";
        tmp+="(";
        tmp.append(node.getNodeName());
        tmp+=")";
        tmp.append(node.getCoordinate());
        tmp+="-";
        tmp.append(std::to_string(node.getNodeId()));
        tmp+="\n";
        cout << tmp;
        fputs(tmp.c_str(),nodeFile );
    });

    fclose(nodeFile);

    FILE* verticeFile;
    verticeFile= fopen(verticeFilePath.c_str(),"w");

    for_each (graph->getVertices().begin(), graph->getVertices().end(), [verticeFile](Vertice vertice) {
        std::string tmp = "";
        tmp+="(";
        tmp.append(std::to_string(vertice.getIteratorNode1()->getNodeId()));
        tmp+=")-(";
        tmp.append(std::to_string(vertice.getIteratorNode2()->getNodeId()));
        tmp+=")[";
        tmp.append(std::to_string(vertice.getWeight()));
        tmp+="]\n";
        cout << tmp;
        fputs(tmp.c_str(),verticeFile );
    });

    fclose(verticeFile);

}

///author jeremy
///
/// This function can be used to get a node entry from the terminal.
/// It asks the user to input the data, which it uses to create a node class.
/// The created node class is then passed to the graph.
///
/// Output node is added to graph
void StorageMngr::getNodeEntryFromScreen() {

    string name = "";
    string coordinateX = "";
    string coordinateY = "";
    string iD = "";
    cout << "Please enter node name: >";
    getline(cin, name);
    cout << "Please enter node coordinate x: >";
    getline(cin, coordinateX);
    cout << "Please enter node coordinate y: >";
    getline(cin, coordinateY);
    cout << "Please enter node iD: >";
    getline(cin, iD);
    graph->addNode(Node(std::stof(coordinateX), std::stof(coordinateY),std::stoi(iD), name ));

}

///author jeremy
///
/// This function can be used to get a vertice entry from the terminal.
/// It asks the user to input the data which, it uses to create a vertice class
/// The created vertice class is then passed to the graph
///
/// Output vertice is added to graph.
void StorageMngr::getVerticeEntryFromScreen() {

    string node1 = "";
    string node2 = "";
    string weight = "";

    cout << "Please enter id of from node x: >";
    getline(cin, node1);
    cout << "Please enter id of to node x: >";
    getline(cin, node2);
    cout << "Please enter path weight x: >";
    getline(cin, weight);
    graph->addVertice(Vertice(graph->getNodeByID(std::stoi(node1)),graph->getNodeByID(std::stoi(node2)),std::stoi(weight)));


}

///author jeremy
///
/// This function is used to start the graph factory
///
/// This function opens the fil streams in append mode
/// and calles the independent node and vertice factories.
/// Afterwards it will close the file streams.
///
/// Output graph is stored in memory
void StorageMngr::RunGraphFactory() {

    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);
    verticeFileStreamIn.open(verticeFilePath,std::ios_base::app);

    RunNodeFactory();
    RunVerticeFactory();

    closeFiles();

}

///author jeremy
///
/// This function handle the parsing of lines found in the node file and the creation of nodes
///
/// This function wil keep getting lines from the file from which it wil extract the node information.
/// This information is stored in strings named after the information they contain.
/// After parsing a line from the file, a node object is created with the data found.
/// This created node is then passed to the graph.
/// This repeats untill there are no more lines in the file.
///
/// !!!
/// If the user enters an entry directly in the file itself, make sure not to end the last
/// with a new line. This will cause the node factories to read an additional empty entry and store it.
/// This causes undefined behavior when iterating over elements in other functions.
/// !!!
///
/// Output nodes are stored in graph
void StorageMngr::RunNodeFactory() {

    string nodeEntry = "";
    while (getline (nodeFileStreamIn,nodeEntry)) {
        string nodeName = "";
        string nodePosX = "";
        string nodePosY = "";
        string nodeId = "";

        bool nameFlag = 0;
        bool coordinateFlagX = 0;
        bool coordinateFlagY = 0;
        bool nodeIdFlag = 0;

        unsigned int i = 0;
        while (i < nodeEntry.length()) {

            char c = nodeEntry.at(i);
            if (c == '(') {
                nameFlag = 1;
            }
            else if (c == ')') {
                nameFlag = 0;
            }
            else if (c == '[') {
                coordinateFlagX = 1;
            }
            else if (c == ']') {
                coordinateFlagY = 0;
            }
            else if (c == ',') {
                coordinateFlagX = 0;
                coordinateFlagY = 1;
            }
            else if (c == '-'){
                nodeIdFlag = 1;
            }

            else {
                if (nameFlag) {
                    nodeName += c;
                }
                if (coordinateFlagX) {
                    nodePosX += c;
                }
                if (coordinateFlagY) {
                    nodePosY += c;
                }
                if (nodeIdFlag) {
                    nodeId += c;
                }
            }
            i++;
        }

        float tmpPosX = std::stof(nodePosX);
        float tmpPosY = std::stof(nodePosY);
        int tmpId = atoi(nodeId.c_str());
        graph->addNode(Node(tmpPosX,tmpPosY, tmpId, nodeName));

    }
}


///author jeremy
///
/// This function handle the parsing of lines found in the vertice file and the creation of vertices
///
/// This function wil keep getting lines from the file from which it wil extract the vertice information.
/// This information is stored in strings named after the information they contain.
/// After parsing a line from the file, a vertice object is created with the data found.
/// in the case of the involved nodes this is done by calling the graph to return the *ptr to the nodes  in the vertice.
/// This is done based on node id.
/// This created vertice is then passed to the graph.
/// This repeats until there are no more lines in the file.
///
/// !!!
/// If the user enters an entry directly in the file itself, make sure not to end the last
/// with a new line. This will cause the node factories to read an additional empty entry and store it.
/// This causes undefined behavior when iterating over elements in other functions.
/// !!!
///
/// Output vertices are stored in graph
void StorageMngr::RunVerticeFactory() {

    string verticeEntry = "";
    while (getline (verticeFileStreamIn,verticeEntry)) {
        string nodeA = "";
        string nodeB = "";
        string weight = "";

        bool nodeFlagA = 0;
        bool nodeFlagB = 0;
        bool weightFlag = 0;


        unsigned int i = 0;
        while (i < verticeEntry.length()) {
            char c = verticeEntry.at(i);

            if (c == '(' && !nodeFlagB) {
                nodeFlagA = 1;
            }
            else if (c == '(' && nodeFlagB) {
                //nothing
            }
            else if (c == ')') {
                nodeFlagA = 0;
                nodeFlagB = 0;

            }
            else if (c == '[') {
                weightFlag = 1;
            }
            else if (c == ']') {
                weightFlag = 0;
            }
            else if (c == '-'){
                    nodeFlagB =1;
            }
            else {
                if (nodeFlagA) {
                    nodeA += c;
                }
                if (nodeFlagB) {
                    nodeB += c;
                }
                if (weightFlag) {
                    weight += c;
                }
            }

            i++;
        }


        int tmpNodeA =  atoi(nodeA.c_str());
        int tmpNodeB =  atoi(nodeB.c_str());
        int tmpWeight =  atoi(weight.c_str());

        graph->addVertice(Vertice(graph->getNodeByID(tmpNodeA), graph->getNodeByID(tmpNodeB), tmpWeight ));
    }
}









