#include <stdio.h>
#include <vector>

using namespace std;

int q;
char l;
char prev;
float val;
vector<float> venda;
vector<float> compra;
float lucro;
char wtf[5];

int c1;



int main() {


	while (scanf("%d", &q) == 1 && q != 0) {

		lucro = 0;
		prev = 'C';
		venda.clear();
		compra.clear();

		for (c1 = 0; c1 < q; c1++) {

			scanf("%s%f", wtf, &val);
			l = wtf[0];
			//printf("%c - %f\n", l, val);

			if (l == 'C') {

				if (venda.size() > 0 &&
					val >= venda.front()) {

					lucro += val - venda.front();
					venda.pop_front();
					venda.sort();
				}

				else {
					if (val >= compra.back()) compra.push_back(val);
					else compra.push_front(val);
					//if (prev != l) compra.sort();
				}
			}

			else {
				if (compra.size() > 0 &&
					val <= compra.back()) {

					lucro += compra.back() - val;
					compra.pop_back();
					compra.sort();
				}

				else {
					if (val <= venda.front()) venda.push_front(val);
					else venda.push_back(val);
					//if (prev != l) venda.sort();
				}
			}
			prev = l;
		}


		printf("%.2f\n", lucro);
	}


	return 0;
}
