#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;

        sf::RenderWindow window(sf::VideoMode(320, 240, 32), "example");
        window.display();
    
    return 0;
}