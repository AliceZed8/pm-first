#include <iostream>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    int a, b, c, N;
    //lab2.1
    std::cin >> a >> b >> c;
    if (a<b && b>c) std::cout << b + a - c << std::endl;
    else if (b % c == 0) std::cout << b / c - b << std::endl;
    else std::cout << a * b - c << std::endl;

    //lab2.2
    std::cin >> N;
    switch (N)
    {
    case 1:
        std::cout << "������" << std::endl;
        break;
    case 2:
        std::cout << "�������" << std::endl;
        break;
    case 3:
        std::cout << "����" << std::endl;
        break;
    case 4:
        std::cout << "������" << std::endl;
        break;
    case 5:
        std::cout << "���" << std::endl;
        break;
    case 6:
        std::cout << "����" << std::endl;
        break;
    case 7:
        std::cout << "����" << std::endl;
        break;
    case 8:
        std::cout << "������" << std::endl;
        break;
    case 9:
        std::cout << "��������" << std::endl;
        break;
    case 10:
        std::cout << "�������" << std::endl;
        break;
    case 11:
        std::cout << "������" << std::endl;
        break;
    case 12:
        std::cout << "�������" << std::endl;
        break;
    default:
        std::cout << "�������� N" << std::endl;
        break;
    }
}