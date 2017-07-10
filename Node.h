//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H


#include <vector>



class Node {
public:
    Node(int id,int x,int y,bool walkable=true,int g=0,int h=0): id(id),x(x),y(y),walkable(walkable),g(g),h(h){};

    int getId() const { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
     std::vector<Node*> &getParents()  { return parents; } //TODO Is it sure not const reference return value?
    int getG() const { return g; }
    int getH() const { return h; }
    int getF() const { return g+h; }
    bool isWalkable() const { return walkable; };
    Node* getComeFrom()  { return comeFrom; };
    void setId(int id) { Node::id = id; }
    void setX(int x) { Node::x = x; }
    void setY(int y) { Node::y = y; }
    void setParents(const std::vector<Node*> &p) { parents = p; }
    void setG(int g) { Node::g = g; }
    void setH(int h) { Node::h = h; }
    void setWalkable(bool walkable) { Node::walkable = walkable; } //FIXME Use this or change parameters name
    void setComeFrom(Node* comeFrom) { Node::comeFrom = comeFrom; }


private:
    int id;
    bool walkable;
    int x,y;
    std::vector<Node*> parents;
    int g,h;
    Node* comeFrom;

};




#endif //PROJECT_NODE_H
