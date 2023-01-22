#include <iostream>

int main() {
    unsigned int k = 1000;
    unsigned int *p = &k;

    for (int i = 0; i < sizeof(k); i++) {
        std::cout << (int)((unsigned char *)p + i) << std::endl;
    }
}