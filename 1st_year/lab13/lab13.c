#include <stdio.h>
#include <stdint.h>


int sep(int x) {
	if (x == ' ' || x == '\n' || x == '\t' || x == ',' || x == EOF) {
		return 1;
	}
	else return 0;
}

int main() {
	int c = 0, st = 0, n = 0, check = -1;
	unsigned  int w_1 = 0, w_2 = 0;
	do {
		c = getchar();
		if (c >= 'A' && c <= 'Z') {
			c += 'a' - 'A';
		}
		switch (st) {
		case 0:
			w_1 = 0;
			if (sep(c)) {
				st = 0;
			}
			else {
				w_1 |= 1u << (c - 'a');
				st = 1;
			}
			break;

		case 1:
			if (sep(c)) {
				st = 2;
				check++;
			}
			else {
				w_1 |= 1u << (c - 'a');
			}
			break;

		case 2:
			w_2 = 0;
			if (sep(c)) {
				st = 2;
			}
			else {
				w_2 |= 1u << (c - 'a');
				st = 3;
			}
			break;

		case 3:
			if (sep(c)) {
				st = 0;
				check++;
			}
			else {
				w_2 |= 1u << (c - 'a');
			}
			break;
		}
		if (check > 0) {
			check--;
			if ((w_1 & w_2) == 0) {
				n++;
			}
		}
	} while (c != EOF);
	if (n) {
		printf("В тектсе есть %d пар(а/ы) соседних слов, составленных из разного набора букв\n", n);
	}
	else {
		printf("В тектсе нет соседних слов, составленных из разного набора букв\n");
	}
}
