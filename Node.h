//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H


#include <vector>


struct Link{
    Node* parent;
    int g;
};

class Node {
public:
    Node(int id,int x,int y,std::vector<Link> parents,int g=0,int h=0): id(id),x(x),y(y),parents(parents),g(g),h(h){};

    int getId() const { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
     std::vector<Link> &getParents() const { return parents; } //TODO Is it sure not const reference return value?
    int getG() const { return g; }
    int getH() const { return h; }
    int getF() const { return g+h; }
    void setId(int id) { Node::id = id; }
    void setX(int x) { Node::x = x; }
    void setY(int y) { Node::y = y; }
    void setParents(const std::vector<Node *> &parents) { Node::parents = parents; }
    void setG(int g) { Node::g = g; }
    void setH(int h) { Node::h = h; }


private:
    int id;
    int x,y;
    std::vector<Link> parents;
    int g,h;  //FIXME G is an attribute of a link, not of a node, remove setter/getter



};


#endif //PROJECT_NODE_H
