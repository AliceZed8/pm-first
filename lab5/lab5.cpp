#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main() {
	setlocale(LC_ALL, "RU");

	//lab 5.1
	char str[] = "привет мир";
	char sym = 'т';
	int i, p = -1;

	for (i = 0; i < strlen(str); i++) {
		if (str[i] == sym) {
			p = i;
			break;
		}
	}
	std::cout << p << std::endl;

	//lab5.2 кодировка ansi

	std::fstream file("C:\\Users\\zoker\\Desktop\\test.txt");
	std::string temp;
	std::vector<std::string> words;
	if (file.is_open()) {
		while (!file.eof()) {
			std::getline(file, temp, ' ');
			words.push_back(temp);
		}
	}

	for (i = 0; i < words.size(); i++) {
		std::cout << words[i];
	}


}