#include <iostream>
#include <vector>
#include "inc/func1.hpp"
#include "inc/func2.hpp"

int main() {
	int i, j, n, m, max, k = 0;
	std::cin >> n >> m;
	std::vector<std::vector<int>> mas(n, std::vector<int>(m));
	std::vector<int> list;

	read(mas, n, m);
	max = get_max(mas, n, m);
	k = count(mas, max, n, m);
	if (k > 1) {
		list = get_primes_list(mas, n, m);
		csort(mas, list, n, m);
	}
	std::cout << "\n";
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cout << mas[i][j] << " ";
		}
		std::cout << "\n";
	}
}
