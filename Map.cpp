//
// Created by ale on 09/07/17.
//

#include "Map.h"
#include <cmath>
#include <algorithm>

void Map::findRoute(Node *start, Node *goal) {
    std::vector<Node *> open;
    std::vector<Node *> close;

    Node *current;
    Node *successor;

    int successor_current_const;

    start->setH(calculateEuristic(start, goal));
    open.push_back(start);

    while (!open.empty()) {
        std::sort(open.begin(), open.end(), [](Node *a, Node *b) { return (a->getF() < b->getF()); });
        current = open[0];

        if (current == goal)
            return; //FIXME It' s logica that we finished but how to get the route back if it s first while cycle?

        for (auto itr = current->getParents().begin(); itr != current->getParents().end(); itr++) {
            successor = (*itr).parent;
            successor_current_const = current->getG() + (*itr).g;  //g(current)+w(current,successor)

            if (std::find(open.begin(), open.end(), successor) != open.end()) {
                if ((*itr).g <= successor_current_const)
                    close.push_back(current);
            } else if (std::find(close.begin(), close.end(), successor) != close.end()) {
                if ((*itr).g <= successor_current_const){
                    close.push_back(current);
                    close.erase(std::remove(close.begin(),close.end(),successor)); //erase-remove idiom
                    open.push_back(successor);
                }
            }

        }


    }

    int Map::calculateEuristic(Node *n, Node *goal) { //Distance between two points
        return static_cast<int>(sqrt(pow(n->getX() - goal->getX(), 2) + pow(n->getY() - goal->getY(), 2)));
    }