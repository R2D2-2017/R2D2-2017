//
// Created by jeremy on 22-5-17.
//

#include "StorageManager.hh"

StorageMngr::StorageMngr(const std::string nodeFilePath, const std::string verticeFilePath):
    nodeFilePath(nodeFilePath), verticeFilePath(verticeFilePath){

}
void StorageMngr::storageSetGraph(Graph * tmp) {
    graph = tmp;

}

void StorageMngr::closeFiles() {
    if (nodeFileStreamIn.is_open()){
        nodeFileStreamIn.close();
    }
    if (verticeFileStreamIn.is_open()){
        verticeFileStreamIn.close();
    }

}

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

void StorageMngr::RunGraphFactory() {

    nodeFileStreamIn.open(nodeFilePath,std::ios_base::app);
    verticeFileStreamIn.open(verticeFilePath,std::ios_base::app);

    RunNodeFactory();
    RunVerticeFactory();

    closeFiles();

}

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









