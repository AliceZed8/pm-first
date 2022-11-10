#ifndef PROJECT_MAP_HPP
#define PROJECT_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "settings.hpp"
class Map {
public:
    Map (sf::RenderWindow& render_window);
    void draw();
    bool checkMapCase(int x, int y);
private:
    sf::RenderWindow& r_window;
    std::vector<std::vector<unsigned int>> vec_map;
    std::vector<sf::RectangleShape> vec_blocks;
    unsigned int xSize, ySize;

};


#endif
