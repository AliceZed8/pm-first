#include <SFML/Graphics.hpp>
#include "inc/settings.hpp"
#include "src/map.cpp"
#include "src/camera.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), L"Псевдо 3D");
    Map m_map(window);
    Camera cam(window, m_map);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear();
        cam.update();
        cam.draw_blocks();
        m_map.draw();
        cam.draw_other();
        window.display();
    }

    return 0;
}