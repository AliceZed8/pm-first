#include <iostream>

int main() {
    int A, i, num, temp, max = 0, sum = 0; 
    std::cin >> A;
    for (i = 0; i < A; i++) {
        std::cin >> temp;
        if (temp < 0 && temp % 7 == 0) sum += temp;
        if (temp > max) {
            max = temp;
            num = i + 1;
        }
    }
    std::cout << sum << " "<< max << " " << num << std::endl;
}