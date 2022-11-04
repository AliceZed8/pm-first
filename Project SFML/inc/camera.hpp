#ifndef _CAMERA_H
#define _CAMERA_H
#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "map.hpp"
#include <cmath>

class Camera {
    private:
        Map& m_map;
        sf::RenderWindow& m_renderWindow;
        sf::CircleShape m_camera;
        sf::Vector2f m_position, m_intersection;
        sf::Clock m_clock;
        float m_angle, m_fov, m_rayLength;
        float m_radius;
        float m_speedMove, m_speedAngle;

        std::vector<sf::VertexArray> m_vecRays;
    public:
        Camera(sf::RenderWindow& renderWindow, Map& map);

        inline float toRadians(float degree) {return degree * (pi / 180.0);}
        
        float getCos(float degree) {
            return std::cos(toRadians(degree));
        }
        float getSin(float degree) {
            return std::sin(toRadians(degree));
        }

    void checkKeyboardHit(sf::Time dt);
    bool intersect(unsigned int it);
    void draw();
    void update();
    void move();
    void projection();
};


#endif