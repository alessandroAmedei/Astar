//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#include <SFML/Graphics.hpp>
#include "Node.h"

class Map : public sf::Drawable {
public:
    Map(int size,bool random=false);
    Map(int size,std::vector<int>& walkables);  //FROM THE INTERNET
    bool findRoute(Node* source,Node* goal);
    Node* getNodeFromCoords(int mx,int my);
    void reset(int what);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Color c1;
    sf::Color c2;
    std::string stringMsg;
    std::string stringFromInternet;

private:
    int _mapsize;
    std::vector<Node *> list;
    std::vector<Node*> getPath(int state,Node* a, Node* b);
    int calculateDistance(Node* a,Node* b);
    void addNeighboursCostr();
};

#endif //PROJECT_MAP_H
