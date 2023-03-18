#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#define PI 3.14159265358979

struct Angle {
    float a, b;
};

struct Point {
    float x, y;
};


class KinematicSolver {
private:
    float l1 = 60.f, l2 = 60.f, x0 = 0, y0 = 0;
    
public:
    float toDegrees(float radians) {
        return radians * (180 / PI);
    }
    KinematicSolver(float length1, float length2) {
        l1 = length1; l2 = length2;
    }

    void SetOrigin(float x, float y) {
        x0 = x; y0 = y;
    }
    
    Angle Solve(float x, float y) {

        float dx = x - x0, dy = y - y0;
        if (std::sqrt(dx * dx + dy * dy) > l1 + l2) {
            return { -9999.f, -9999.f };
        }
        float cos_b = ( dx * dx + dy * dy - (l1 * l1 + l2 * l2) ) / (2 * l1 * l2);
        float sin_b = std::sqrt(1 - cos_b * cos_b);
        float b = std::acos(cos_b);
        float a = std::atan(dy / dx) - std::atan((l2 * sin_b) / (l1 + l2 * cos_b));
        
        
        return { a,b };
    }


    bool checkPoint(float& x, float& y) {
        return (std::sqrt(x * x + y * y) <= l1 + l2) && (std::sqrt(x * x + y * y) >= std::abs(l1 - l2));
    }

    bool checkAngles(Angle & ang, Point &pnt) {
        float sresx = l1 * std::cos(ang.a) + l2 * std::cos(ang.a + ang.b);
        float sresy = l1 * std::sin(ang.a) + l2 * std::sin(ang.a + ang.b);
        float x = pnt.x - x0;
        float y = pnt.y - y0;
        return
            ((x - 1.f <= sresx) && (sresx <= x + 1.f)) &&
            ((y - 1.f <= sresy) && (sresy <= y + 1.f));
            

    }


    void Generate(std::vector<Point>& vector) {
        //Парабола 0.1*x*x

        for (float x = -50.f; x <= 50.f; x += 0.5f) {
            float y = 0.1f * x * x;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }
        //Окружность с радиусом 50 пикс, с центром в (80, -80) в новой системе координат
        float r = 50.f;
        float posx = 80.f;
        float posy = -80.f;

        for (float x = posx - r; x <= posx + r; x += 0.3f) {
            float y = std::sqrt(r * r - std::pow((x - posx), 2)) +  posy;

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float x = posx - r; x <= posx + r ; x += 0.3f) {
            float y = -std::sqrt(r * r - std::pow((x - posx), 2)) + posy;

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        //эллипс
        float a = 300.f, b = 200.f;
        for (float x = -a; x <= a; x += 0.5f) {
            float y = std::sqrt(b * b * (1 - ((x * x) / (a * a))));

            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        //Квадрат

        for (float x = -200.f; x <= -50.f; x += 1.f) {
            float y = -50.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }
        
        for (float y = -50.f; y>= -200.f; y -= 1.f) {
            float x = -50.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float x = -50.f; x >= -200.f; x -= 1.f) {
            float y = -200.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }

        for (float y = -200.f; y <= -50.f; y += 1.f) {
            float x = -200.f;
            if (checkPoint(x, y)) vector.push_back({ x0 + (x), y0 - (y) });
        }
        


    }

    
};





int main() {
    unsigned int WIDTH= 800, HEIGHT = 800;
    float l1 = 200.f, l2 = 150.f;
    float x0 = WIDTH/2, y0 = HEIGHT/2;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Test");

    //Solver
    KinematicSolver solver(l1, l2);
    solver.SetOrigin(x0, y0);

    //Joints
    sf::RectangleShape joint1{ sf::Vector2f(l1, 4.f) };
    sf::RectangleShape joint2{ sf::Vector2f(l2, 4.f) };
    
    joint1.setPosition(x0, y0);
    joint1.setFillColor(sf::Color::Color(60,60,60));
    joint2.setFillColor(sf::Color::Color(60,60,60));

    //Ox
    sf::RectangleShape Ox{ sf::Vector2f(WIDTH, 1.f) };
    Ox.setPosition(0, y0);
    Ox.setFillColor(sf::Color::Black);

    //Oy
    sf::RectangleShape Oy{ sf::Vector2f(HEIGHT, 0.5f) };
    Oy.setPosition(x0, 0);
    Oy.rotate(90);
    Oy.setFillColor(sf::Color::Black);

    //Main Point
    sf::CircleShape pmain{ 4.0f };
    pmain.setOrigin(2.0f, 2.0f);
    pmain.setFillColor(sf::Color::Green);

    //Массив точек
    std::vector<Point> array;


    //Генерация точек параболы
    solver.Generate(array);

    unsigned int k = 0;
    bool ok = false;
    bool pause = false;

    std::vector<sf::CircleShape> buffer;
    sf::CircleShape point(4.f);
    point.setOrigin(2.f, 2.f);
    point.setFillColor(sf::Color::Blue);

    //шрифт
    sf::Font font;
    font.loadFromFile("font.ttf");

    //Текст
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(5.f, 5.f);
    text.setFillColor(sf::Color::Black);
    std::string str("Joints: ");
    std::string final;
    str += std::to_string(l1) + " " + std::to_string(l2) + "\n";




    //Framerate
    float want_fps = 60;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Точка
        auto pnt = array[k];
        Angle ang = solver.Solve(pnt.x, pnt.y);
        ok = true;

        //Если робот не достает
        if ((ang.a == -9999.f) && (ang.b == -9999.f)) ok = false;

        window.clear(sf::Color::White);

        //Оси
        window.draw(Ox);
        window.draw(Oy);

        //Следующая точка
        k++;

        for (const auto& elem : buffer) window.draw(elem);

        if (ok && !pause) {
            point.setPosition(pnt.x, pnt.y);
            buffer.push_back(point);
            
            //Конечный текст
            final = str +
                "Alpha: " + std::to_string(std::abs(solver.toDegrees(ang.a))) + "\n" +
                "Beta: " + std::to_string(std::abs(solver.toDegrees(ang.b)));
            text.setString(final);
            
          
            //Проверка совпадения точек
            if (solver.checkAngles(ang, pnt))
            {
                joint1.setRotation(solver.toDegrees(ang.a));

                joint2.setPosition(x0 + l1 * std::cos(ang.a), y0 + l1 * std::sin(ang.a));
                joint2.setRotation(solver.toDegrees(ang.a + ang.b));
            }
            else {
                joint1.setRotation(solver.toDegrees(ang.a) + 180);

                joint2.setPosition(x0 - l1 * std::cos(ang.a), y0 - l1 * std::sin(ang.a));
                joint2.setRotation(solver.toDegrees(ang.a + ang.b) + 180);
            }

            //Ведущая точка
            pmain.setPosition(pnt.x, pnt.y);
        }

        window.draw(joint1);
        window.draw(joint2);
        window.draw(pmain);
        window.draw(text);
        window.display();


        //Сброс или пауза после прохождения всех точек
        if (k >= array.size()) {
            k = 0;
            pause = true;
        }


        sf::Int32 frame_duration = clock.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / want_fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        clock.restart();
    }

    return 0;
}