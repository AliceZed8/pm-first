#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

int main() {
    const int WIDTH= 800, HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}