#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int tx, ty;
int qp, px, py;
bool tab[250000];
int q;
int c1, c2;

int x1, y1, x2, y2;

int buff;
int main() {

	while (scanf("%d %d %d", &tx, &ty, &qp) == 3 && tx != 0) {

		memset(tab, 0, ty * tx);
		q = 0;

		for (; qp > 0; qp--) {

			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1--;
			y1--;
			x2--;
			y2--;
			if (x1 > x2) {
				buff = x1;
				x1 = x2;
				x2 = buff;
			}
			if (y1 > y2) {
				buff = y1;
				y1 = y2;
				y2 = buff;
			}

			//printf("Lol: %d %d %d %d\n", x1, y1, x2, y2);


			for (c1 = y1; c1 <= y2; c1++) {
				for (c2 = x1; c2 <= x2; c2++) {
					if (tab[c1*tx + c2] == 0) q++;
				}
				memset(&tab[c1*tx + x1], 1, x2 - x1 + 1);
			}
		}

		q = (tx * ty) - q;
		printf("There ");
		if (q == 0) printf("is no");
		else if (q == 1) printf("is one");
		else printf("are %d", q);
		printf(" empty spot");
		if (q != 1) putchar('s');
		printf(".\n");

	}

	return 0;
}
