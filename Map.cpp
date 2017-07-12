//
// Created by ale on 09/07/17.
//

#include "Map.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

Map::Map(int size) : _mapsize(size + 2) {

    int distance = 1200 / size;

    for (int r = 0; r < _mapsize; r++) {
        for (int j = 0; j < _mapsize; j++) {

            if (r == 0 || j == 0)
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, false, false));

            else if (r == _mapsize - 1 || j == _mapsize - 1)
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, false, false));

            else
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, true, false));
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

    c1 = sf::Color::Blue;
    c2 = sf::Color::Blue;

}

void Map::findRoute(int x, int y, int x1, int y1) {  //FIXME CHeck if we need this
    findRoute(list[x * _mapsize + y], list[x1 * _mapsize + y1]);
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
        std::sort(open.begin(), open.end(),
                  [](Node *a, Node *b) { return (a->getF() < b->getF()); }); //FIXME If it s equal check H!
        current = open[0]; //Take from open list the node current with the lowest f

        open.erase(std::remove(open.begin(), open.end(), current));
        close.push_back(current);

        if (current == goal)
            getPath(0,start, goal); // THERE IS A WAY

        for (auto itr = current->getParents().begin();
             itr != current->getParents().end(); itr++) {  //For each node successor of the current node

            neighbour = (*itr);

            if (!neighbour->isWalkable() || std::find(close.begin(), close.end(), neighbour) != close.end())
                continue;

            int newMovementCostToNeighbour = current->getG() + calculateDistance(current, neighbour);

            if (newMovementCostToNeighbour < neighbour->getG() ||
                std::find(open.begin(), open.end(), neighbour) == open.end()) {
                neighbour->setG(newMovementCostToNeighbour);
                neighbour->setH(calculateDistance(neighbour, goal));
                neighbour->setComeFrom(current);

                if (std::find(open.begin(), open.end(), neighbour) == open.end())
                    open.push_back(neighbour);
            }
        }
    }
}

int Map::calculateDistance(Node *a, Node *b) {
    int x = abs(a->getX() - b->getX());
    int y = abs(a->getY() - b->getY());

    if (x > y)
        return 14 * y + 10 * (x - y);
    return 14 * x + 10 * (y - x);
}

std::vector<Node *> Map::getPath(int state,Node *a, Node *b) {

    std::vector<Node *> path;
    Node *current = b;
    std::cout << "The fastest route is" << std::endl;
    while (a != current) {
        std::cout << current->getId() << " ";
        current->setSelected(true);
        path.push_back(current);
        current = current->getComeFrom();
    }


    return path;
}

void Map::buildWall(int x, int y, bool state) {
    list[x * _mapsize + y]->setWalkable(state);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    int nodesize = (1200 / (_mapsize - 2)) - 1;

    sf::Texture texture;
    if (!texture.loadFromFile(
            "/home/ale/CLionProjects/Astar/tiles/greengrayred.png")) {  //FIXME Bad! we don't want absolute path
        std::cout << "error, can't find tiles" << std::endl;
    }

    for (int i = 0; i < list.size(); i++) {

        sf::VertexArray quad(sf::Quads, 4);

        int x = list[i]->getX();
        int y = list[i]->getY();

        quad[0].position = sf::Vector2f(x, y + nodesize);
        quad[1].position = sf::Vector2f(x, y);
        quad[2].position = sf::Vector2f(x + nodesize, y);
        quad[3].position = sf::Vector2f(x + nodesize, y + nodesize);
        if (list[i]->isWalkable() == false) {
            quad[0].texCoords = sf::Vector2f(200, 50);
            quad[1].texCoords = sf::Vector2f(200, 20);
            quad[2].texCoords = sf::Vector2f(200, 20);
            quad[3].texCoords = sf::Vector2f(200, 10);
        }
        if (list[i]->isSelected() == true) {
            quad[0].texCoords = sf::Vector2f(600, 50);
            quad[1].texCoords = sf::Vector2f(600, 20);
            quad[2].texCoords = sf::Vector2f(600, 20);
            quad[3].texCoords = sf::Vector2f(600, 10);
        }

        target.draw(quad, &texture);
    }

    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("/home/ale/CLionProjects/Astar/fonts/arial.ttf")) {
        std::cout << "error, can't find arial font";
    }

    text.setFont(font);
    text.setString(
            "                                    AStar Maze Solver \n Created by Alessandro Amedei and Edith Ehrenbrandtner \n                                UniFirenze & UniPassau");
    text.setColor(sf::Color::Blue);
    text.setPosition(1700, 40);

    sf::Text wall;
    wall.setFont(font);
    wall.setString("Build Wall");
    wall.setColor(c1);
    wall.setPosition(1900, 330);

    sf::Text path;
    path.setFont(font);
    path.setString("Select Nodes");
    path.setColor(c2);
    path.setPosition(1900, 530);


    target.draw(text);
    target.draw(wall);
    target.draw(path);

}

Node *Map::getNodeFromCoords(int mx, int my) {

    int nodesize = (1300 / (_mapsize - 2)) - 1;

    for (int i = 0; i < list.size(); i++) {

        int x = list[i]->getX();
        int y = list[i]->getY();

        if (mx > x && mx < x + nodesize && my > y && my < y + nodesize)
            return list[i];
    }
    return nullptr;
}


