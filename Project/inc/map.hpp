#ifndef PROJECT_MAP_HPP
#define PROJECT_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map (sf::RenderWindow r_window);
private:
    sf::RenderWindow r_window;
    std::vector<std::vector<unsigned int>> vec_map;
};


#endif
