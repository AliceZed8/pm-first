#include <iostream>
#include <vector>

std::vector<std::vector<int>> read(int n, int m) {
	std::vector<std::vector<int>> mas(n, std::vector<int>(m));
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cin >> mas[i][j];
		}
	}
	return mas;
}
