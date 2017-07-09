//
// Created by ale on 09/07/17.
//

#ifndef PROJECT_NODE_H
#define PROJECT_NODE_H


#include <vector>

class Node {
public:
    Node(int id,int x,int y,std::vector<Node*> parents,int g=0,int h=0): id(id),x(x),y(y),parents(parents),g(g),h(h){};

    int getId() const { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
    const std::vector<Node *> &getParents() const { return parents; }
    int getG() const { return g; }
    int getH() const { return h; }
    void setId(int id) { Node::id = id; }
    void setX(int x) { Node::x = x; }
    void setY(int y) { Node::y = y; }
    void setParents(const std::vector<Node *> &parents) { Node::parents = parents; }
    void setG(int g) { Node::g = g; }
    void setH(int h) { Node::h = h; }


private:
    int id;
    int x,y;
    std::vector<Node*> parents;
    int g,h;



};


#endif //PROJECT_NODE_H
