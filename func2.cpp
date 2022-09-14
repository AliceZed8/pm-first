#include <iostream>
#include <vector>

int get_max(std::vector<std::vector<int>> mas, int n, int m ) {
	int i, j, max = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (mas[i][j] > max) {
				max = mas[i][j];
			}
		}
	}

	return max;
}

int count(std::vector<std::vector<int>> mas, int el, int n, int m) {
	int i, j, k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (mas[i][j] == el) k++;
		}
	}
	return k;
}

int get_dels(int num) {
	int i, k = 0;
	for (i = 2; i < (num / 2) + 1; i++) {
		if (num % i == 0) k++;
	}
	return k;
	}

std::vector<int> get_primes_list(std::vector<std::vector<int>> mas, int n, int m) {
	std::vector<int> primes_c_list;
	int i, j, dels =0, k;
	for (i = 0; i < n; i++) {
		k = 0;
		for (j = 0; j < m; j++) {
			dels = get_dels(mas[i][j]);
			if (dels == 0) k++;
		}
		primes_c_list.push_back(k);
	}
	return primes_c_list;
}

std::vector<std::vector<int>> csort(std::vector<std::vector<int>> mas, std::vector<int> list, int n, int m) {
	int i, j, t, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if (list[j] < list[j + 1]) {
				t = list[j +1];
				list[j + 1] = list[j];
				list[j] = t;
				for (k = 0; k < m; k++) {
					t = mas[j + 1][k];
					mas[j + 1][k] = mas[j][k];
					mas[j][k] = t;
				}
			}
		}
	}
	return mas;
}


