#ifndef _MAP_H
#define _MAP_H
#include <SFML/Graphics.hpp>
#include "settings.hpp"

class Map {
    private:
    sf::RenderWindow& m_renderWindow;
    std::vector<std::vector<unsigned int>> m_vecMap;
    std::vector<sf::RectangleShape> m_vecBox;

    public:
        Map(sf::RenderWindow& renderWindow);
        void draw();
        void update();
        bool checkMapCase(unsigned int dx, unsigned int dy);
};

#endif