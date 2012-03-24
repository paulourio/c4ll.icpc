#include <stdio.h>

int q;
char l, prev;
float val;
int c, v;
float compra[50000], venda[50000];
int maiorcomp, menorvend;
float lucro;
char wtf[5];

int c1;

/*

int achapos(float *arr, float p) {
	int cl, cr, mid;

	while (cl <= cr) {
		mid = (cl + cr) / 2;

		if (arr[mid] == p) return mid;
		*/

void acha_maior_compra() {
	if (c == 0) {
		maiorcomp = -1;
		return;
	}
	maiorcomp = 0;
	int cc;
	for (cc = 1; cc < c; cc++) {
		if (compra[cc] > compra[maiorcomp]) maiorcomp = cc;
	}
}


void acha_menor_venda() {
	if (v == 0) {
		menorvend = -1;
		return;
	}
	menorvend = 0;
	int cc;
	for (cc = 1; cc < v; cc++) {
		if (venda[cc] > venda[menorvend]) menorvend = cc;
	}
}

int main() {


	while (scanf("%d", &q) == 1 && q != 0) {

		c = 0;
		v = 0;
		maiorcomp = -1;
		menorvend = -1;
			lucro = 0;
		for (c1 = 0; c1 < q; c1++) {

			scanf("%s%f", wtf, &val);
			l = wtf[0];
			//printf("%c - %f\n", l, val);
			prev = l;

			if (l == 'C') {
				if (v > 0 && val >= venda[menorvend]) {
					//printf("Lucro: %f (%f)C.\n", lucro, val - venda[menorvend]);
					lucro += (val - venda[menorvend]);
					v--;
					if (menorvend < v) venda[menorvend] = venda[v];
					acha_menor_venda();
				}
				else if (c == 0) {
					c = 1;
					compra[0] = val;
					maiorcomp = 0;
				}
				else {
					compra[c] = val;
					c++;
					if (val > compra[maiorcomp]) maiorcomp = c-1;
				}
			}

			else {
				if (c > 0 && val <= compra[maiorcomp]) {
					//printf("Lucro: %f (%f).\n", lucro, compra[maiorcomp] - val);
					lucro += (compra[maiorcomp] - val);
					c--;
					if (maiorcomp < c) compra[maiorcomp] = compra[c];
					acha_maior_compra();
				}
				else if (v == 0) {
					v = 1;
					venda[0] = val;
					menorvend = 0;
				}
				else {
					venda[v] = val;
					v++;
					if (val < venda[menorvend]) menorvend = c-1;
				}
			}
		}


		printf("%.2f\n", lucro);
	}


	return 0;
}
