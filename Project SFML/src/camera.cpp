#include "../inc/camera.hpp"

Camera::Camera(sf::RenderWindow& renderWindow, Map& map):
    m_renderWindow(renderWindow), m_map(map)
{
    m_radius = 1;
    m_camera.setRadius(m_radius);
    m_camera.setFillColor(sf::Color::Green);
    m_camera.setOrigin(sf::Vector2f(m_radius, m_radius));
    m_speedMove = 200.0f;
    m_speedAngle = 100.0f;
    m_angle = 0.0f;
    m_position = sf::Vector2f({128, 128});
    m_fov = 60;
    m_rayLength = 100;

    for (unsigned int i = 0; i < WIDTH; i++) {
        sf::VertexArray ray(sf::Lines, 2);
        ray[0].color = sf::Color::Red;
        ray[1].color = sf::Color::Red;
        m_vecRays.push_back(ray);
    }
}

void Camera::draw() {
    for (unsigned int i = 0;  i < m_vecRays.size(); i++) {
        m_renderWindow.draw(m_vecRays[i]);
    }
    m_renderWindow.draw(m_camera);
}
void Camera::update() {
    sf::Time dt = m_clock.restart();
    checkKeyboardHit(dt);
    projection();
}

void Camera::projection() {
    for (unsigned int i = 0; i < m_vecRays.size(); i++) {
        m_vecRays[i][0].position = m_position;

        if (intersect(i)) {
            m_vecRays[i][1].position = m_intersection;
        } else {
        m_vecRays[i][1].position = {m_position.x + m_rayLength * getCos((m_angle + m_fov/2) - i*(m_fov/WIDTH)),
                                    m_position.y + m_rayLength * getSin((m_angle + m_fov/2) - i*(m_fov/WIDTH))};       
        }
    }
}

void Camera::checkKeyboardHit(sf::Time dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!(m_map.checkMapCase((m_position.x + getCos(m_angle)*m_speedMove*dt.asSeconds())/blockSize, (m_position.y + getSin(m_angle)*m_speedMove*dt.asSeconds())/blockSize))) {
            m_position.x += getCos(m_angle)*m_speedMove*dt.asSeconds();
            m_position.y += getSin(m_angle)*m_speedMove*dt.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!(m_map.checkMapCase((m_position.x - getCos(m_angle)*m_speedMove*dt.asSeconds())/blockSize, (m_position.y - getSin(m_angle)*m_speedMove*dt.asSeconds())/blockSize))) {
            m_position.x -= getCos(m_angle)*m_speedMove*dt.asSeconds();
            m_position.y -= getSin(m_angle)*m_speedMove*dt.asSeconds();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_angle -= m_speedAngle*dt.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_angle += m_speedAngle*dt.asSeconds();
    }

    if (m_angle > 360) m_angle = 0;
    if (m_angle < 0) m_angle = 360;

    m_camera.setPosition(m_position);
    m_camera.setRotation(m_angle);
}

bool Camera::intersect(unsigned int it) {
    float fAngle = m_angle + (m_fov/2) - (it*(m_fov/WIDTH));
    sf::Vector2f direction = {getCos(fAngle), getSin(fAngle)};

    for (unsigned int i = 0; i < m_rayLength; i++) {
        int dx = (int)(m_position.x + i*direction.x);
        int dy = (int)(m_position.y + i*direction.y);

        if (m_map.checkMapCase(dx/blockSize, dy/blockSize)) {
            m_intersection.x = dx;
            m_intersection.y = dy;
            return true;
        }

    }
    return false;
}