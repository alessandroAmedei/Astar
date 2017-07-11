//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H


#include "Node.h"


class Map {
public:
    Map(int size);
    void findRoute(int x,int y,int x1,int y1);
    void builWall(int x,int y,bool state);
private:
    int _mapsize;
    std::vector<Node *> list;
    std::vector<Node*> getPath(Node* a, Node* b);
    int calculateDistance(Node* a,Node* b);
    void findRoute(Node* source,Node* goal);

};


#endif //PROJECT_MAP_H
