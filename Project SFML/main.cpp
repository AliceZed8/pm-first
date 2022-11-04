#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/camera.cpp"
#include "src/map.cpp"

int main () {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML", sf::Style::Titlebar);
    window.setFramerateLimit(60);
    Map _map (window);
    Camera cam(window, _map);
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                
            }
        }
        cam.update();
        window.clear();
        cam.draw();
        _map.draw();
        window.display();
    }
}