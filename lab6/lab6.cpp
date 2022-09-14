#include <iostream>
#include <vector>
#include "func1.cpp"

int main() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> mas(n, std::vector<int>(m));
	mas = read(n, m);
}