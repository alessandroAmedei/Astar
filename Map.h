//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Node.h"


class Map : public sf::Drawable {
public:
    Map(int size);
    void findRoute(int x,int y,int x1,int y1);
    void findRoute(Node* source,Node* goal);
    void buildWall(int x,int y,bool state);
    Node* getNodeFromCoords(int mx,int my);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Color c1;
    sf::Color c2;

private:
    int _mapsize;
    std::vector<Node *> list;
    std::vector<Node*> getPath(int state,Node* a, Node* b);
    int calculateDistance(Node* a,Node* b);



};


#endif //PROJECT_MAP_H
