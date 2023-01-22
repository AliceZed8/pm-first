#include <iostream>

int main() {
	int n, i, j, k, t;

	//lab 4.1
	int mas1[10000];
	bool flag = false;

	std::cin >> n;

	for (i = 0; i < n; i++) {
		k = 0;
		std::cin >> t;
		mas1[i] = t;
		for (j = 2; j <= t / 2 + 1; j++) {
			if (t % j == 0) {
				k++;
				break;
			}
		}
		if (k == 0) flag = true;
	}
	if (flag == false) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n - 1; j++) {
				if (mas1[j] > mas1[j + 1]) {
					t = mas1[j];
					mas1[j] = mas1[j+1];
					mas1[j + 1] = t;	
				}
			}
		}
	}
	for (i = 0; i < n; i++) {
		std::cout << mas1[i] << " ";
	}
	std::cout << "\n";


	//lab 4.2
	int mas2[3][1000], p = 1, s = 0, t1, t2, t3;

	std::cin >> n;

	for (i = 0; i < n; i++) {
		std::cin >> t;
		s = 0;
		p = 1;
		mas2[0][i] = t;
		while (t > 0) {
			j = t % 10;
			t = t / 10;
			s += j;
			p *= j;
		}
		mas2[1][i] = s;
		mas2[2][i] = p;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if (mas2[1][j] > mas2[1][j + 1]) {
				t1 = mas2[0][j];
				t2 = mas2[1][j];
				t3 = mas2[2][j];
				mas2[0][j] = mas2[0][j + 1];
				mas2[1][j] = mas2[1][j + 1];
				mas2[2][j] = mas2[2][j + 1];
				mas2[0][j + 1] = t1;
				mas2[1][j + 1] = t2;
				mas2[2][j + 1] = t3;
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if ((mas2[1][j] == mas2[1][j + 1]) && (mas2[2][j] > mas2[2][j + 1])) {
				t1 = mas2[0][j];
				t2 = mas2[1][j];
				t3 = mas2[2][j];
				mas2[0][j] = mas2[0][j + 1];
				mas2[1][j] = mas2[1][j + 1];
				mas2[2][j] = mas2[2][j + 1];
				mas2[0][j + 1] = t1;
				mas2[1][j + 1] = t2;
				mas2[2][j + 1] = t3;
			}
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if ((mas2[1][j] == mas2[1][j + 1]) && (mas2[2][j] == mas2[2][j + 1]) && (mas2[0][j] > mas2[0][j + 1])) {
				t1 = mas2[0][j];
				t2 = mas2[1][j];
				t3 = mas2[2][j];
				mas2[0][j] = mas2[0][j + 1];
				mas2[1][j] = mas2[1][j + 1];
				mas2[2][j] = mas2[2][j + 1];
				mas2[0][j + 1] = t1;
				mas2[1][j + 1] = t2;
				mas2[2][j + 1] = t3;
			}
		}
	}

	for (i = 0; i < n; i++) {
		std::cout << mas2[0][i] << " ";
	}
	std::cout << "\n";
	

	//lab 4.3
	int n, m, mp = 0, mi, mas3[100][100];

	std::cin >> n >> m;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			std::cin >> t;
			mas3[i][j] = t;
		}
	}
	for (i = 0; i < n; i++) {
		p = 1;
		for (j = 0; j < m; j++) {
			p *= mas3[i][j];
		}
		if (p > mp) {
			mp = p;
			mi = i;
		}
	}
	for (j = 0; j < m; j++) {
		mas3[i][j] = mp;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) std::cout << mas3[i][j] << " ";
		std::cout << "\n";
	}
}