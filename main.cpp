#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Map.h"


int main() {


    sf::RenderWindow window (sf::VideoMode(800,600),"Maze");


    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){

            if(event.type==sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        sf::Sprite sprite;
        sf::Texture texture;
        if(!texture.loadFromFile("/home/ale/CLionProjects/Astar/grass2.jpeg")){
            std::cout<<"error"<<std::endl;
        }

        sprite.setTextureRect(sf::IntRect(10,10,64,64));
        sprite.setTexture(texture);

        window.draw(sprite);
        window.display();
    }

    Map m(5);

    m.builWall(2,2,false);
    m.builWall(2,3,false);
    m.builWall(2,4,false);
    m.builWall(3,3,false);
    m.builWall(4,3,false);
    m.builWall(5,3,false);



    m.findRoute(3,2,5,4);






    return 0;
}
