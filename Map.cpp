//
// Created by ale on 09/07/17.
//

#include "Map.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

Map::Map(int size, bool random) : _mapsize(size + 2) {

    int distance = 1250 / size;
    int randval;
    srand(time(0));

    for (int r = 0; r < _mapsize; r++) {
        for (int j = 0; j < _mapsize; j++) {

            if (r == 0 || j == 0)
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, false, false));

            else if (r == _mapsize - 1 || j == _mapsize - 1)
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, false, false));

            else {
                if (random)  //FIXME Everytime it has to control if it s random.. make it before the for loop.
                    randval = rand() % 3;
                else
                    randval = 1;
                list.push_back(new Node(r * _mapsize + j, r * distance + 40, j * distance + 40, randval, false));
            }
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
    stringMsg="";
}

void Map::reset(int what) {
    if (what == 0) {
        for (int i = 0; i < list.size(); i++) {
            list[i]->setSelected(false);
            stringMsg = false;
        }
    }
    if (what == 1) {
        bool walkable;
        //  list[i]->setWalkable(true); //FIXME It makes walkable also the walles at the border..
        for (int r = 0; r < _mapsize; r++) {
            for (int j = 0; j < _mapsize; j++) {
                if (r == 0 || j == 0)
                    walkable = false;
                else if (r == _mapsize - 1 || j == _mapsize - 1)
                    walkable = false;
                else
                    walkable = true;
                list[r * _mapsize + j]->setWalkable(walkable);
            }
        }
    }
    if (what == 2) {
        for (int i = 0; i < list.size(); i++) {
            list[i]->setG(0);
            list[i]->setH(0);
        }
    }
}

void Map::findRoute(Node *start, Node *goal) {
    reset(2);

    std::vector<Node *> open;
    std::vector<Node *> close;

    Node *current;
    Node *neighbour;

    int newMovementCostToNeighbour=0;

    start->setH(calculateDistance(start, goal));  //Put start in open list and set F to H (because G=0)
    open.push_back(start);

    while (!open.empty()) {  //While open is not empty
        std::sort(open.begin(), open.end(),
                  [](Node *a, Node *b) { return (a->getF() < b->getF()); }); //FIXME If it s equal check H!
        current = open[0]; //Take from open list the node current with the lowest f

        open.erase(std::remove(open.begin(), open.end(), current));
        close.push_back(current);

        if (current == goal) {
            getPath(0, start, goal); // THERE IS A WAY
            return;
        }

        for (auto itr = current->getParents().begin();
             itr != current->getParents().end(); itr++) {  //For each node successor of the current node

            neighbour = (*itr);

            if (!neighbour->isWalkable() || std::find(close.begin(), close.end(), neighbour) != close.end())
                continue;

            newMovementCostToNeighbour = current->getG() + calculateDistance(current, neighbour);

            if (newMovementCostToNeighbour < neighbour->getG() || std::find(open.begin(), open.end(), neighbour) == open.end()) {
                neighbour->setG(newMovementCostToNeighbour);
                neighbour->setH(calculateDistance(neighbour, goal));
                neighbour->setComeFrom(current);

                if (std::find(open.begin(), open.end(), neighbour) == open.end())
                    open.push_back(neighbour);
            }
        }
    }
    getPath(-1, nullptr, nullptr);
}

int Map::calculateDistance(Node *a, Node *b) {
    int x = abs(a->getX() - b->getX());
    int y = abs(a->getY() - b->getY());
    //if (x > y)
    //  return 14 * y + 10 * (x - y);
    //return 14 * x + 10 * (y - x);
    return (sqrt(x * x + y * y));  //JUst calculate the distance between two points (left top corner of every node)
}

std::vector<Node *> Map::getPath(int state, Node *a, Node *b) {
    std::vector<Node *> path;
    if (state == -1) {
        stringMsg = "Astar didn't find a route";
        return path;
    } else {
        stringMsg = "Astar found a route \n cost: " + std::to_string(b->getF());

        Node *current = b;
        while (a != current) {
            current->setSelected(true);
            path.push_back(current);
            current = current->getComeFrom();
        }
        return path;
    }
}

Node *Map::getNodeFromCoords(int mx, int my) {
    int nodesize = (1250 / (_mapsize - 2)) - 1;
    for (int i = 0; i < list.size(); i++) {
        int x = list[i]->getX();
        int y = list[i]->getY();
        if (mx > x && mx < x + nodesize && my > y && my < y + nodesize)
            return list[i];
    }
    return nullptr;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    int nodesize = (1250 / (_mapsize - 2)) - 1;

    sf::Texture texture;
    if (!texture.loadFromFile("/home/ale/CLionProjects/Astar/tiles/greengrayred.png")) {  //FIXME Bad! we don't want absolute path
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
            quad[0].texCoords = sf::Vector2f(700, 150);
            quad[1].texCoords = sf::Vector2f(600, 20);
            quad[2].texCoords = sf::Vector2f(600, 20);
            quad[3].texCoords = sf::Vector2f(600, 10);
        }

        target.draw(quad, &texture);
    }

    sf::Font font;
    if (!font.loadFromFile("/home/ale/CLionProjects/Astar/fonts/arial.ttf")) {
        std::cout << "error, can't find arial font";
    }

    sf::Text text("AStar MazeSolver \n Alessandro Amedei \n UniFI", font, 35);
    text.setStyle(sf::Text::Italic);
    text.setColor(sf::Color::Blue);
    text.setPosition(1750, 40);

    sf::Text wall("Build Wall", font);
    wall.setColor(c1);
    wall.setPosition(1820, 550);

    sf::Text reset2(" || Reset || Random", font);
    reset2.setColor(sf::Color::Blue);
    reset2.setPosition(2000, 550);

    sf::Text path("Select Nodes", font);
    path.setColor(c2);
    path.setPosition(1800, 650);

    sf::Text reset(" || Reset", font);
    reset.setColor(sf::Color::Blue);
    reset.setPosition(2000, 650);

    sf::Text size("Map Size  20x20  30x30  50x50", font);
    size.setColor(sf::Color::Blue);
    size.setPosition(1670, 450);

    sf::Text textMsg(stringMsg, font, 50);
    textMsg.setPosition(1700, 900);
    textMsg.setColor(sf::Color::Green);

    target.draw(text);
    target.draw(wall);
    target.draw(reset2);
    target.draw(path);
    target.draw(reset);
    target.draw(size);
    target.draw(textMsg);

}
