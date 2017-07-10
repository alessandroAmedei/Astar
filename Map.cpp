//
// Created by ale on 09/07/17.
//

#include "Map.h"
#include <cmath>
#include <algorithm>
#include <iostream>

void Map::findRoute(Node *start, Node *goal) {
    std::vector<Node *> open;
    std::vector<Node *> close;

    Node *current;
    Node *neighbour;

    int successor_current_const;

    start->setH(calculateDistance(start, goal));  //Put start in open list and set F to H (because G=0)
    open.push_back(start);

    while (!open.empty()) {  //While open is not empty
        std::cout<<"open not empty"<<std::endl;
        std::sort(open.begin(), open.end(), [](Node *a, Node *b) { return (a->getF() < b->getF()); }); //FIXME If it s equal check H!
        current = open[0]; //Take from open list the node current with the lowest f

        open.erase(std::remove(open.begin(),open.end(),current));
        close.push_back(current);

        if (current == goal)
            getPath(start,goal);

        for(auto itr = current->getParents().begin() ; itr != current->getParents().end() ; itr++){  //For each node successor of the current node

            neighbour=(*itr);

            if(!neighbour->isWalkable() || std::find(close.begin(),close.end(),neighbour) != close.end())
                continue;

            int newMovementCostToNeighbour = current->getG() + calculateDistance(current,neighbour);

            if(newMovementCostToNeighbour<neighbour->getG() || std::find(open.begin(),open.end(),neighbour) == open.end()){
                neighbour->setG(newMovementCostToNeighbour);
                neighbour->setH(calculateDistance(neighbour,goal));
                neighbour->setComeFrom(current);

                if(std::find(open.begin(),open.end(),neighbour) == open.end())
                    open.push_back(neighbour);
            }
        }
    }
}



std::vector<Node*> Map::getPath(Node *a, Node *b) {
    std::cout << "Now i should give you the path "<<std::endl;

    std::vector<Node*> path;
    Node* current=b;

    while(a!=current){
        std::cout<<current->getId()<< " ";
        path.push_back(current);
        current=current->getComeFrom();
    }
    std::cout<<std::endl;
    std::reverse(path.begin(),path.end());

    return path;
}

int Map::calculateDistance(Node *a, Node *b) {
    int x = abs(a->getX()-b->getX());
    int y = abs(a->getY()-b->getY());

    if(x>y)
        return 14*y + 10*(x-y);
    return 14*x + 10*(y-x);
}


