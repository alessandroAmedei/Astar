#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Map.h"


int main() {

    Map m(50);



    m.findRoute(3,2,5,4);


    sf::RenderWindow window (sf::VideoMode(2560,1600),"Maze");


    bool buildWall=true;
    bool selectNodes=false;
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){

            if(event.type==sf::Event::Closed)
                window.close();
            if(event.type==sf::Event::MouseButtonPressed){
                std::cout<< event.mouseButton.x << "  "<< event.mouseButton.y << std::endl;
                Node* n = m.getNodeFromCoords(event.mouseButton.x,event.mouseButton.y);
              if(n!=nullptr){
                  if(buildWall)
                      n->setWalkable(false);
              }
            }
        }
        window.clear(sf::Color::White);


        window.draw(m);
        window.display();
    }








    return 0;
}
