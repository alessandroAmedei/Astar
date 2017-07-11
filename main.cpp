#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Map.h"


int main() {

    Map m(10);



    m.findRoute(3,2,5,4);


    sf::RenderWindow window (sf::VideoMode(1600,1220),"Maze");


    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){

            if(event.type==sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);


        window.draw(m);
        window.display();
    }








    return 0;
}
