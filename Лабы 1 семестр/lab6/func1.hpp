#include <iostream>
#include <vector>

void read(std::vector<std::vector<int>> &mas, int n, int m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cin >> mas[i][j];
		}
	}
}
