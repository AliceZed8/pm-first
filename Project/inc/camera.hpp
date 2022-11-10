#ifndef PROJECT_CAMERA_HPP
#define PROJECT_CAMERA_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "map.hpp"
#include <cmath>
class Camera {
private:
    Map& map;
    sf::RenderWindow& r_window;
    sf::CircleShape camera;
    float angle, fov, ray_length, radius, move_speed, sens_speed, sensivity;
    sf::Vector2f m_position, m_intersection;
    sf::Clock clock;
    std::vector<sf::VertexArray> vec_rays, vec_fbl, vec_sky_blocks, vec_floor_blocks;

public:
    Camera(sf::RenderWindow& window, Map& m_map);
    void update();
    void projection();
    void draw_blocks();
    void draw_other();
    void checkKeyboard(sf::Time deltaTime);
    bool intersect(unsigned int i_num);
    float toRad(float degree) {return (degree * PI) / 180; }
    float getSin(float degree) {return std::sin(toRad(degree));}
    float getCos(float degree) {return std::cos(toRad(degree));}
};


#endif
