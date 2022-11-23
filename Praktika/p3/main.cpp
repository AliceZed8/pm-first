#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const unsigned int R1 = (int) L'А', R2 = (int) L'Я',
                    r1 = (int) L'а', r2 = (int) L'я', step = 32;


int its(wchar_t ch) {
    if (((int) ch >= R1) && ((int) ch <= R2)) return 1;
    else if (((int) ch >= r1) && ((int) ch <= r2)) return 0;
    else return -1;
}

wchar_t toLower(wchar_t &ch) {
    return (wchar_t ) (( int) ch + step);
}

wchar_t toUpper(wchar_t &ch) {
    return (wchar_t ) (( int) ch - step);
}


int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::locale locale("ru_RU.utf-8");
    std::vector <std::wstring> words;


    std::wifstream file("/home/alicezed/Рабочий стол/pm-first/Praktika/p3/input.txt");
    file.imbue(locale);

    if (file.is_open()) {
        std::cout << "READ" << std::endl;
        while (!file.eof()) {
            std::wstring temp;
            file >> temp;
            words.push_back(temp);
        }
    } file.close();


    std::wofstream out("/home/alicezed/Рабочий стол/pm-first/Praktika/p3/output.txt");
    out.imbue(locale);

    if (out.is_open()) {
        std::cout << "WRITE" << std::endl;
            for (unsigned int p = 0; p < words.size(); p++) {
                std::cout << "Word " << p + 1 << "/" << words.size() << std::endl;
                if (words[p].length() > 6) {
                    wchar_t a[4];
                    bool match = false;

                    for (unsigned int j = 0; j < words[p].length() - 3; j++) {
                        bool cont = true;

                        for (unsigned int k = 0; k < 4; k++) {
                            switch (its(words[p][j + k])) {
                                case 1:
                                    a[k] = toLower(words[p][j + k]);
                                    break;
                                case 0:
                                    a[k] = words[p][j + k];
                                    break;
                                default:
                                    cont = false;
                                    break;
                            }
                        }

                        if (cont) {
                            if (((int) a[0] < (int) a[1]) && ((int) a[1] < (int) a[2]) && ((int) a[2] < (int) a[3])) {
                                match = true;
                                words[p][j] = toUpper(a[0]);
                                words[p][j + 1] = toUpper(a[1]);
                                words[p][j + 2] = toUpper(a[2]);
                                words[p][j + 3] = toUpper(a[3]);
                                break;
                            }
                        }
                    }

                    if (match) {
                        if (p == 0) out << words[p] << L" (" << a[0] << L", " << a[1] << L", " << a[2] << L", " << a[3] << L" )";
                        else out << L" " << words[p] << L" (" << a[0] << L", " << a[1] << L", " << a[2] << L", " << a[3] << L" )";
                    } else {
                        if (p== 0) out << words[p];
                        else out << L" " << words[p];
                    }
                } else {
                    if (p== 0) out << words[p];
                    else out << L" " << words[p];
                }
            }
        }
    out.close();
}

