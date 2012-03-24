#include <stdio.h>


int q;
char l, buffchar;
unsigned short val, buff;

unsigned short VENDA[100004], COMPRA[100004];
unsigned short *venda, *compra;
int c, v;

long lucro;

int c1;


int comp(void *p1, void *p2) {
	return (*((unsigned short *) p1) - *((unsigned short *) p2));
}

void printv(unsigned short *arr, int tam) {
	int ccc;
	if (tam == 0) printf("[");
	for (ccc = 0; ccc < tam; ccc++) {
		printf("%c%hu", (ccc == 0)? '[' : ' ', arr[ccc]);
	}
	printf("]\n");
}

int acha_pos(unsigned short *arr, int q, unsigned short valor) {

	int l = 0, r = q-1;
	int mid;
	if (q == 0 || valor <= arr[l]) return 0;
	if (valor >= arr[r]) return q;

	while (l < r) {
		mid = (l + r) / 2;
		if (valor >= arr[mid] && valor <= arr[mid + 1]) return mid + 1;
		if (valor < arr[mid]) r = mid - 1;
		else l = mid + 1;
	}
	return l+1;
}

void create_space(unsigned short **arr, int q, int pos) {

	int ccc;
	if (pos > q/2) {
		for (ccc = q; ccc > pos; ccc--) (*arr)[ccc] = (*arr)[ccc-1];
	}
	else {
		(*arr)--;
		for (ccc = 0; ccc < pos; ccc++) (*arr)[ccc] = (*arr)[ccc+1];
	}
}

void insert(unsigned short **arr, int *q, unsigned int valor) {
	int pos = acha_pos(*arr, *q, valor);
	//printf("Pos: %d/%d\n", pos, *q);
	create_space(arr, *q, pos);
	(*q)++;
	(*arr)[pos] = valor;
}



int main() {
	int newline = 1;

	while (scanf("%d", &q) == 1 && q != 0) {
		fgetc(stdin);

		lucro = 0;
		c = 0;
		v = 0;
		venda = &VENDA[50002];
		compra = &COMPRA[50002];

		for (c1 = 0; c1 < q; c1++) {

			scanf("%c%c%hu%c%hu%c", &l, &buffchar, &val, &buffchar, &buff, &buffchar);
			val *= 100;
			val += buff;
			//printf("Val: %hu, l: %c\n", val, l);

			if (l == 'C') {

				if (v > 0 && val >= venda[0]) {
					lucro += val - venda[0];
					venda++;
					v--;
				}

				else insert(&compra, &c, val);
			}

			else {
				if (c > 0 && val <= compra[c-1]) {
					lucro += compra[c-1] - val;
					c--;
				}

				else insert(&venda, &v, val);
			}
			//printf("L: (%hu) %hu.%02hu\n", val, lucro/100, lucro%100);
			//printv(compra, c);
			//printv(venda, v);
			//printf("\n");
		}

		if (newline == 0) printf("\n");
		printf("%ld.%02ld", lucro/100, lucro%100);
		newline = 0;
	}


	return 0;
}
/*

int main() {

	unsigned short arr2[20] = {0, 0, 0, 0, 0, 0, 0, 0, 10, 20, 30, 30, 30, 40, 50};
	unsigned short *arr = &arr2[8];
	int q = 7;

	insert(&arr, &q, 5);
	printv(arr, q);

	insert(&arr, &q, 60);
	printv(arr, q);

	insert(&arr, &q, 15);
	printv(arr, q);

	insert(&arr, &q, 10);
	printv(arr, q);

	insert(&arr, &q, 30);
	printv(arr, q);

	insert(&arr, &q, 35);
	printv(arr, q);

	insert(&arr, &q, 25);
	printv(arr, q);

	insert(&arr, &q, 40);
	printv(arr, q);

	return 0;


	printf("%d\n", acha_pos(arr, 7, 5));
	printf("%d\n", acha_pos(arr, 7, 60));
	printf("%d\n", acha_pos(arr, 7, 15));
	printf("%d\n", acha_pos(arr, 7, 10));
	printf("%d\n", acha_pos(arr, 7, 30));
	printf("%d\n", acha_pos(arr, 7, 35));
	printf("%d\n", acha_pos(arr, 7, 25));
	printf("%d\n", acha_pos(arr, 7, 40));
}
*/
