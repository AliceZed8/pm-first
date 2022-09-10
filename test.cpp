#include <iostream>
#include <algorithm>
int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    int s, h, a, b, c, N, A, i;
    
        
    //v6
    // lab1
    std::cin >> s >> h;
    std::cout << (s * h)/3 << std::endl;


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
        std::cout << "Januar" << std::endl;
        break;
    case 2:
        std::cout << "Февраль" << std::endl;
        break;
    case 3:
        std::cout << "Март" << std::endl;
        break;
    case 4:
        std::cout << "Апрель" << std::endl;
        break;
    case 5:
        std::cout << "Май" << std::endl;
        break;
    case 6:
        std::cout << "Июнь" << std::endl;
        break;
    case 7:
        std::cout << "Июль" << std::endl;
        break;
    case 8:
        std::cout << "Август" << std::endl;
        break;
    case 9:
        std::cout << "Сентябрь" << std::endl;
        break;
    case 10:
        std::cout << "Октябрь" << std::endl;
        break;
    case 11:
        std::cout << "Ноябрь" << std::endl;
        break;
    case 12:
        std::cout << "Декабрь" << std::endl;
        break;
    default:
        std::cout << "Неверное N" << std::endl;
        break;
    }

    //lab 3
    std::cin >> A;
    int max = 0, num, sum, temp;
    for (i = 0; i < A; i++) {
        std::cin >> temp;
        if (temp < 0 && temp % 7 == 0) sum += temp;
        if (temp > max) {
            max = temp;
            num = i + 1;
        }
    }
    std::cout << sum << max << num << std::endl;


    //lab4.1

    short j, k , flag = 0, count;
    int mas[10000];

    for (i = 0; i < j; i++) {
        std::cin >> temp;
        count = 0;
        mas[i] = temp;

        for (k = 2; k <= temp / 2 + 1; k++) {
            if (temp % k == 0) count++;
        }
        if (count == 0) flag = 1;
    }

    if (flag == 0) std::sort(std::begin(mas), std::end(mas));
    for (i = 0; i < j; i++) {
        std::cout << mas[i] << std::endl;
    }


    






}