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
    std::vector<Node*> getPath(Node* a, Node* b);
    int calculateDistance(Node* a,Node* b);
};


#endif //PROJECT_MAP_H
