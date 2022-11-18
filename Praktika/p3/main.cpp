#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>


std::map <char, unsigned int> mp;

int main() {
    setlocale(LC_CTYPE, "RUSSIAN");

    std::ifstream file("inpt.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            std::string word;
            file >> word;

            std::cout << word << std::endl;
        }
    }

    std::string ms = "абв";
    ms[0] = (char) std::toupper(ms[0]);

    std::cout << ms << std::endl;

    std::ofstream out_file("output.txt");

    if (out_file.is_open()) {
        out_file << ms << std::endl;
    }

}