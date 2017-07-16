//
// Created by Alessandro Amedei on 14/07/17.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"

void playSound(int what) {

    static sf::SoundBuffer sb;  //They can not go out of scope (sound is a thread!)
    static sf::Sound sound;

    switch (what) {
        case 0:
            sb.loadFromFile("/home/ale/CLionProjects/Astar/sounds/a.wav");
            break;
        case 1:
            sb.loadFromFile("/home/ale/CLionProjects/Astar/sounds/b.wav");
    }
    sound.setBuffer(sb);
    sound.setPlayingOffset(sf::seconds(0.2));
    sound.play();
}

bool isConnection() {  //TODO SFML doesn't provide a way to check internet connection.
    return true;
}

std::string getTextFromInternet(int what) {
    if (!isConnection())
        return "error";

    try {
        sf::Http http;

        http.setHost("http://ame97software.altervista.org/");

        sf::Http::Request request("/astar/get.php", sf::Http::Request::Post);
        request.setHttpVersion(1, 1);
        if (what == 1)
            request.setBody("value=1");

        sf::Http::Response response = http.sendRequest(request);

        if (response.getStatus() == sf::Http::Response::Ok)
            return response.getBody();
        else
            return "error";
    } catch (std::exception e) {
        return "error";
    }
}

int main() {

    Map m(30);

    sf::RenderWindow window(sf::VideoMode(2560, 1600), "Maze");

    bool buildWall = false;
    bool selectNodes = false;
    int count = 0;
    int mapsize = 30;
    Node *source;
    Node *goal;
    while (window.isOpen()) {

        m.stringFromInternet = getTextFromInternet(0);

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                //   std::cout << event.mouseButton.x << "  " << event.mouseButton.y << std::endl;
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                Node *n = m.getNodeFromCoords(x, y);
                if (n != nullptr) {
                    playSound(1);
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
                        } else if (count == 1 && source != n) {
                            goal = n;
                            goal->setSelected(true);
                            m.findRoute(source, goal);
                            count = 0;
                        }
                    }
                    n = nullptr;
                } else if (x > 1811 && x < 1811 + 200 && y > 555 && y < 555 + 40) {
                    if (buildWall) {
                        buildWall = false;
                        m.c1 = sf::Color::Blue;
                    } else {
                        buildWall = true;
                        m.c1 = sf::Color::Red;
                        m.c2 = sf::Color::Blue;
                        selectNodes = false;
                    }
                    playSound(0);
                } else if (x > 1795 && x < 1795 + 200 && y > 655 && y < 655 + 40) {
                    playSound(0);
                    if (selectNodes) {
                        selectNodes = false;
                        m.c2 = sf::Color::Blue;
                    } else {
                        selectNodes = true;
                        m.c2 = sf::Color::Red;
                        m.c1 = sf::Color::Blue;
                        buildWall = false;
                    }
                } else if (x > 2030 && x < 2030 + 120 && y > 655 && y < 655 + 40) {
                    playSound(0);
                    m.reset(0);
                    count = 0;
                } else if (x > 2060 && x < 2060 + 80 && y > 555 && y < 555 + 40) {
                    playSound(0);
                    m.reset(1);
                } else if (x > 2140 && x < 2140 + 120 && y > 555 && y < 555 + 40) {
                    playSound(0);
                    m = Map(mapsize, true);
                } else if (y > 455 && y < 455 + 20) {
                    if (x > 1810 && x < 1810 + 90) {
                        playSound(0);
                        m = Map(mapsize = 20);
                    }
                    if (x > 1910 && x < 1910 + 90) {
                        playSound(0);
                        m = Map(mapsize = 30);
                    }
                    if (x > 2000 && x < 2000 + 90) {
                        playSound(0);
                        m = Map(mapsize = 50);
                    }
                    if (x > 2090 && x < 2090 + 90) {
                        playSound(0);
                        std::string s = getTextFromInternet(1);
                        if (s.compare("error") == 0)
                            m.stringFromInternet = s;
                        else {
                            std::cout << s << std::endl;
                            std::cout << s.size() << std::endl;
                            std::vector<char> walkables(s.begin(), s.end());
                            std::vector<int> w(walkables.begin(), walkables.end());  //Trasform string to int vector
                            m = Map(mapsize = 30, w);
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(m);
        window.display();
    }
    return 0;
}

