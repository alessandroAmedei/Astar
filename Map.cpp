//
// Created by ale on 09/07/17.
//

#include "Map.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Map::Map(int size): _mapsize(size+2) {




    for (int r = 0; r < _mapsize; r++) {
        for (int j = 0; j < _mapsize; j++) {

            if (r == 0 || j == 0)
                list.push_back(new Node(r * _mapsize + j, r * 10, j * 10, false));

            else if (r == _mapsize - 1 || j == _mapsize - 1)
                list.push_back(new Node(r * _mapsize + j, r * 10, j * 10, false));

            else
                list.push_back(new Node(r * _mapsize + j, r * 10, j * 10));  //FIXME _mapsize not magic number

        }
    }

    for (int r = 1; r < _mapsize - 1; r++) {
        for (int j = 1; j < _mapsize - 1; j++) {

            std::vector<Node *> &neighbour = list[r * _mapsize + j]->getParents();


            neighbour.push_back(list[(r - 1) * _mapsize + j + 1]);
            neighbour.push_back(list[(r - 1) * _mapsize + j]);
            neighbour.push_back(list[(r - 1) * _mapsize + j - 1]);

            neighbour.push_back(list[(r) * _mapsize + j + 1]);
            neighbour.push_back(list[(r) * _mapsize + j - 1]);

            neighbour.push_back(list[(r + 1) * _mapsize + j + 1]);
            neighbour.push_back(list[(r + 1) * _mapsize + j]);
            neighbour.push_back(list[(r + 1) * _mapsize + j - 1]);

        }
    }




    std::cout << std::endl;

    for (int r = 0; r < _mapsize; r++) {
        for (int j = 0; j < _mapsize; j++) {
            std::cout << list[r * _mapsize + j]->isWalkable() << " ";
        }
        std::cout << std::endl;
    }

}

void Map::findRoute(int x, int y, int x1, int y1) {
    findRoute(list[x*_mapsize+y],list[x1*_mapsize+y1]);
}


void Map::findRoute(Node *start, Node *goal) {
    std::vector<Node *> open;
    std::vector<Node *> close;

    Node *current;
    Node *neighbour;

    int successor_current_const;

    start->setH(calculateDistance(start, goal));  //Put start in open list and set F to H (because G=0)
    open.push_back(start);

    while (!open.empty()) {  //While open is not empty
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

    std::vector<Node*> path;
    Node* current=b;

    while(a!=current){
        std::cout<<current->getId()<< " ";
        path.push_back(current);
        current=current->getComeFrom();
    }

    std::cout<<a->getId()<< " ";
    std::cout<<std::endl;
    std::reverse(path.begin(),path.end());

    return path;
}

void Map::builWall(int x, int y,bool state) {
    list[x*_mapsize+y]->setWalkable(state);
}

int Map::calculateDistance(Node *a, Node *b) {
    int x = abs(a->getX()-b->getX());
    int y = abs(a->getY()-b->getY());

    if(x>y)
        return 14*y + 10*(x-y);
    return 14*x + 10*(y-x);
}


