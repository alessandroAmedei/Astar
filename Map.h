//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H


#include <SFML/Graphics/Drawable.hpp>
#include "Node.h"


class Map : public sf::Drawable {
public:
    Map(int size);
    void findRoute(int x,int y,int x1,int y1);
    void builWall(int x,int y,bool state);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    int _mapsize;
    std::vector<Node *> list;
    std::vector<Node*> getPath(Node* a, Node* b);
    int calculateDistance(Node* a,Node* b);
    void findRoute(Node* source,Node* goal);

};


#endif //PROJECT_MAP_H
