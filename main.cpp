#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Map.h"


int main() {

    Map m(30);




    sf::RenderWindow window(sf::VideoMode(2560, 1600), "Maze");


    bool buildWall = false;
    bool selectNodes = false;
    int count = 0;
    Node *source;
    Node *goal;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << event.mouseButton.x << "  " << event.mouseButton.y << std::endl;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                Node *n = m.getNodeFromCoords(x, y);
                if (n != nullptr) {
                    if (buildWall) {
                        if (n->isWalkable())
                            n->setWalkable(false);
                        else
                            n->setWalkable(true);
                    } else if (selectNodes) {
                        if (count == 0) {
                            source = n;
                            source->setSelected(true);
                            count++;
                        } else if (count == 1) {
                            goal = n;
                            goal->setSelected(true);
                            m.findRoute(source, goal);
                            count = 0;

                        }


                    }
                    n = nullptr;
                } else if (x > 1811 && x < 1811 + 200 && y > 555 && y < 555 + 40) {
                    if (buildWall)
                        buildWall = false;
                    else {
                        buildWall = true;
                        std::cout << "Build wall now!" << std::endl;
                        m.c1 = sf::Color::Red;
                        m.c2 = sf::Color::Blue;
                        selectNodes = false;
                    }
                } else if (x > 1795 && x < 1795 + 200 && y > 655 && y < 655 + 40) {
                    if (selectNodes)
                        selectNodes = false;
                    else {
                        std::cout << "Select nodes now!" << std::endl;
                        selectNodes = true;
                        m.c2 = sf::Color::Red;
                        m.c1 = sf::Color::Blue;
                        buildWall = false;
                    }
                } else if(y>455 && y<455+20){
                    if(x>1810 && x<1810+90)
                        m=Map(20);
                    if(x>1910 && x<1910+90)
                        m=Map(30);
                    if(x>2000 && x<2000+90)
                        m=Map(50);
                }


            }
        }
        window.clear(sf::Color::White);


        window.draw(m);
        window.display();
    }


    return 0;
}

