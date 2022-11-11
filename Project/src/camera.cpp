#include "../inc/camera.hpp"
#include <iostream>
Camera::Camera(sf::RenderWindow &window, Map &m_map):
    r_window(window), map(m_map) {
        m_position = {36, 36};
        angle = 0;
        fov = 60;
        ray_length = 300.0f;
        move_speed = 25.0f;
        sensivity = 1.0f;
        sens_speed = 50.0f;
        radius = 3.0f;
        camera.setRadius(radius);
        camera.setOrigin(sf::Vector2f(radius, radius));
        camera.setFillColor(sf::Color::Green);

        for (unsigned int i = 0; i < WIDTH; i++ ) {
            sf::VertexArray ray (sf::Lines, 2);
            vec_rays.push_back(ray);
            vec_fbl.push_back(ray);
            vec_sky_blocks.push_back(ray);
            vec_floor_blocks.push_back(ray);
        }
}


void Camera::update() {
    sf::Time deltaTime = clock.restart();
    projection();
    checkKeyboard(deltaTime);
}


void Camera::draw_blocks() {
    for (unsigned int i = 0; i < vec_fbl.size(); i++) {
        r_window.draw(vec_fbl[i]);
        r_window.draw(vec_sky_blocks[i]);
        r_window.draw(vec_floor_blocks[i]);
    }
}

void Camera::draw_other() {
    for (unsigned int i = 0; i < vec_rays.size(); i++) {
        r_window.draw(vec_rays[i]);
    }
    r_window.draw(camera);
}


void Camera::projection() {
    for (unsigned int i = 0 ; i < vec_rays.size(); i++) {
        vec_rays[i][0].position = m_position;
        vec_rays[i][0].color = sf::Color::Red;

        if (intersect(i)) {
            vec_rays[i][1] = m_intersection;
            vec_rays[i][1].color = sf::Color::Red;

            float z = std::sqrt(std::pow(m_position.x - m_intersection.x, 2) + std::pow(m_position.y - m_intersection.y, 2));
            float bl_height = (HEIGHT * 16) / z;
            //Стены
            vec_fbl[i][0].position = {(float) WIDTH - i, 360 - bl_height/2};
            vec_fbl[i][1].position = {(float) WIDTH - i, 360 + bl_height/2};
            vec_fbl[i][0].color = sf::Color(0, 255, 0,  255 - z);
            vec_fbl[i][1].color = sf::Color(0, 255, 0, 255 - z);
            //Небо
            vec_sky_blocks[i][0].position = {(float) WIDTH - i, 0};
            vec_sky_blocks[i][1].position = {(float) WIDTH - i, 360 - bl_height/2};
            vec_sky_blocks[i][0].color = sf::Color::Cyan;
            vec_sky_blocks[i][1].color = sf::Color::Cyan;
            //Пол
            vec_floor_blocks[i][0].position = {(float) WIDTH - i, 360 + bl_height/2};
            vec_floor_blocks[i][1].position = {(float) WIDTH - i, 720};
            vec_floor_blocks[i][0].color = sf::Color(150, 75, 0);
            vec_floor_blocks[i][1].color = sf::Color(150, 75, 0);


        } else {
            vec_rays[i][1].position = {
                    m_position.x + ray_length * getCos(angle + fov/2 - i*(fov/WIDTH)),
                    m_position.y + ray_length * getSin(angle + fov/2 - i*(fov/WIDTH))
            };
        }

    }
}


void Camera::checkKeyboard(sf::Time deltaTime) {
    /*
     * Управление
     */
    sf::Vector2f add;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        add = {getCos(angle)*move_speed*deltaTime.asSeconds(),
               getSin(angle)*move_speed*deltaTime.asSeconds()};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        add = {
                -getCos(angle) * move_speed * deltaTime.asSeconds(),
                -getSin(angle) * move_speed * deltaTime.asSeconds()
        };
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (180 >= angle >=0) {
            add = {
                    getCos(90 - angle)*move_speed*deltaTime.asSeconds(),
                    -getSin(90 - angle)*move_speed*deltaTime.asSeconds()
            };
        }
        else {
            add = {
                    -getCos(angle - 180) * move_speed * deltaTime.asSeconds(),
                    getSin(angle - 180) * move_speed * deltaTime.asSeconds()
            };
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (180 >= angle >=0) {
            add = {
                    - getCos(90 - angle)*move_speed*deltaTime.asSeconds(),
                    getSin(90 - angle)*move_speed*deltaTime.asSeconds()
            };

        } else {
            add = {
                    getCos(angle - 180) * move_speed * deltaTime.asSeconds(),
                    -getSin(angle - 180) * move_speed * deltaTime.asSeconds()
            };
        }
    }


    if (!map.checkMapCase((m_position.x + add.x)/blockSize, (m_position.y + add.y)/blockSize)) {
        m_position.x += add.x;
        m_position.y += add.y;
    }

    int delta = sf::Mouse::getPosition(r_window).x - 640;
    angle += delta*sensivity*deltaTime.asSeconds()*sens_speed;
    sf::Mouse::setPosition({640, 360}, r_window);


    camera.setPosition(m_position);
    if (angle > 360) angle = 0;
    if (angle < 0) angle = 360;
}

bool Camera::intersect(unsigned int i_num) {
    float r_angle = angle + fov/2 - i_num*(fov/WIDTH);
    sf::Vector2f direction = {getCos(r_angle), getSin(r_angle)};
    for (unsigned int i = 0; i < ray_length; i++) {
        int dx = (int) (m_position.x + i*direction.x);
        int dy = (int) (m_position.y + i*direction.y);
        if (map.checkMapCase(dx/blockSize, dy/blockSize)) {
            m_intersection.x = dx;
            m_intersection.y = dy;
            return true;
        }
    }
    return false;
}