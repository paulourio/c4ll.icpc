#include <stdio.h>

int main() {
	int q = 100000 + rand() % 6;
	int q2;


	for (;q > 0; q--) {
		q2 = 20 + rand() % 31;
		printf("%d\n", q2);

		for (;q2 > 0; q2--) {
			int val = 1 + rand() % 40000;
			printf("%c %d.%0.2d\n", (rand() % 2)? 'C' : 'V', val/100, val%100);
		}
	}
	printf("0");
	return 0;
}
