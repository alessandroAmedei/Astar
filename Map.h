//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H


#include "Node.h"

class Map {
public:
    void findRoute(Node* source,Node* goal);
private:
    int calculateEuristic(Node* n,Node* goal);
    std::vector<Node*> nodes;
};


#endif //PROJECT_MAP_H
