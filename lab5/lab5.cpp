#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main() {
	setlocale(LC_ALL, "RU");
	int i;
	std::fstream file("test.txt");

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