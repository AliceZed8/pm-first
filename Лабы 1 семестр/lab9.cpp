#include <iostream>
#include <cmath>
class Cube {
    private:
        double size = 1;
    public:
        Cube(int size) {
            this->size = (double) size;
        }
        Cube(long long size) {
            this->size = (double) size;
        }
        Cube(double size) {
            this->size = size;
        }

        double volume() const {
            return std::pow(this->size, 3);
        }

};


int main() {
    Cube c (11);

    std::cout << c.volume() << std::endl;

}