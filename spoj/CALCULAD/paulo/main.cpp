#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <stack>

using namespace std;
double memory[26];
#define MEMORY(chr)	memory[chr - 'a']
#define ISNUM(chr)	'0' <= (chr) && (chr) <= '9'
#define ISVAR(chr)	'a' <= (chr) && (chr) <= 'z'
#define ISPAR(chr)	((chr) == '(' || (chr) == ')')
#define ISOP(c)		((c) == '*' || (c) == '/' || (c) == '+' || (c) == '-')
char buffer[5000001];

int prec(int op)
{
	switch (op) {
	case '/': 
	case '*': return 3;
	case '+': 
	case '-': return 1;
	}
	return -100;
}

enum {VARIAVEL, NUMERO, OPERADOR, PARENTESE};
int token(int value)
{
	if (ISNUM(value))	return NUMERO;
	if (ISVAR(value))	return VARIAVEL;
	if (ISPAR(value))	return PARENTESE;
	return OPERADOR;
}

stack<char *> ops;
list<char *> pfix;

void desempilhar(void)
{
	char *top = ops.top();
	ops.pop();
	pfix.push_back(top);
}

double eval(char *ptr)
{
	pfix.clear();
	while (*ptr != 0) {
		switch(token((int) *ptr)) {
		case VARIAVEL:
			pfix.push_back(ptr++);
			break;
		case NUMERO: 
			pfix.push_back(ptr);
			while (ISNUM(*ptr)) ptr++;
			break;
		case PARENTESE:
			if (*ptr == '(') {
				ops.push(ptr);
			} else {
				while (*ops.top() != '(')
					desempilhar();
				ops.pop();
			}
			ptr++;
			break;
		case OPERADOR:
			while (!ops.empty()) {
				char *top = ops.top();
				if (prec(*top) - prec(*ptr) < 0)
					break;
				desempilhar();
			}
			ops.push(ptr++);
		}
	}
	while (!ops.empty())
		desempilhar();

/*	cerr << "Posfixo: " ;
	for (list<char *>::iterator i=pfix.begin(); i!=pfix.end(); i++)
		cerr << *(*i);
	cerr << endl;
*/
	stack<double> pilha;
	while (!pfix.empty()) {
		char *t = pfix.front();
		pfix.pop_front();

		if (ISOP(*t)) {
			double b = pilha.top(); pilha.pop();
			double a = pilha.top(); pilha.pop();
			double r;
			switch(*t) {
			case '*': r = a * b; break;
			case '/': r = a / b; break;
			case '+': r = a + b; break;
			case '-': r = a - b; break;
			}
			cerr << "Resultado " << a << " " << *t << " " << b << " = " << r << endl;
			pilha.push(r);
			continue;
		}
		if (ISVAR(*t)) 
			pilha.push( (double) MEMORY(*t) );
		else if (ISNUM(*t)) 
			pilha.push( (double) strtoul(t, NULL, 10) );

	}
	return pilha.top();
}

int main(void)
{
	memset(memory, 0, sizeof(memory));
	while (scanf("%s", buffer) == 1) 
		if (buffer[1] == '=')
			MEMORY(*buffer) = eval(buffer + 2);
		else
			printf("%.2f\n", eval(buffer));
	return 0;
}

