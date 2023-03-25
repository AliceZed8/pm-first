#include <iostream>
#include <cmath>

struct Vector2 {
    double x, y;
    Vector2(double x, double y): x(x), y(y) {}
    Vector2(): x(0), y(0) {}
};

struct Color {
    short r, g, b, a;
    Color(short r, short g, short b, short a): r(r), g(g), b(b), a(a) {}
    Color() : r(255),  g(255), b(255), a(255) {}
};

class Shape {
protected:
    Vector2 coord;
    Color color;

public:
    void SetCoords(const Vector2& v) noexcept {
        coord = v;
    }
    Vector2 GetCoords() const  noexcept {
        return coord;
    }

    void SetColor(const Color& col) noexcept {
        color = col;
    }
    Color GetColor() const noexcept {
        return color;
    }

    virtual double GetArea() const noexcept {}
};

class Triangle final: public Shape {
    double a, b, c;

public:
    Triangle(double  a, double b, double c): a(a), b(b), c(c) {}

    double GetArea()  const noexcept override {
        double p = (a + b + c) / 2;
        return std::sqrt(p * (p-a) * (p-b) * (p-c));
    }
};

class Rectangle final: public Shape {
private:
    double a, b;

public:
    Rectangle(double a, double b): a(a), b(b) {};

    double GetArea() const noexcept override {
        return a*b;
    }
};

class Circle final: public Shape {
    double r;
public:
    Circle(double r): r(r) {}
    double GetArea() const noexcept override {
        return M_PI * r * r;
    }
};

int main() {
    Triangle a(3, 4, 5);
    a.SetColor({1, 2, 3, 4});
    a.SetCoords({20, 20});

    Vector2 coord = a.GetCoords();
    Color col = a.GetColor();
    printf("Triangle\n");
    printf("Color: r %d g %d b %d a %d \n", col.r, col.g, col.b, col.a);
    printf("Coords: x %f y %f \n", coord.x, coord.y);
    printf("Area: %f\n", a.GetArea());

    Rectangle rect(3, 4);
    rect.SetColor({1, 2, 3, 4});
    rect.SetCoords({20, 20});

    Vector2 rcoord = rect.GetCoords();
    Color rcol = rect.GetColor();

    printf("Rectangle\n");
    printf("Color: r %d g %d b %d a %d \n", rcol.r, rcol.g, rcol.b, rcol.a);
    printf("Coords: x %f y %f \n", rcoord.x, rcoord.y);
    printf("Area: %f\n", rect.GetArea());


    Circle c(3);
    c.SetColor({1, 2, 3, 4});
    c.SetCoords({20, 20});

    Vector2 ccoord = c.GetCoords();
    Color ccol = c.GetColor();
    printf("Circle\n");
    printf("Color: r %d g %d b %d a %d \n", ccol.r, ccol.g, ccol.b, ccol.a);
    printf("Coords: x %f y %f \n", ccoord.x, ccoord.y);
    printf("Area: %f\n", c.GetArea());

}
