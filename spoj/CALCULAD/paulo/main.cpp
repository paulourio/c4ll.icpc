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
char buffer[6000001];

#ifdef DEBUG
#define err(...)	fprintf(stderr, __VA_ARGS__)
#else
#define err(...)
#endif

int prec(int op)
{
	switch (op) {
	case '/': 
	case '*': return 3;
	case '+': 
	case '-': return 1;
	}
	return 6; /* parentesis? */
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
	err("exp: %s\n", buffer);
	pfix.clear();
	while (*ptr != 0) {
		switch(token((int) *ptr)) {
		case VARIAVEL:
			pfix.push_back(ptr++);
			break;
		case NUMERO: 
		ler_numero:
			pfix.push_back(ptr++);
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
			if (ptr == buffer ||
					( (ISOP(ptr[-1]) || ptr[-1] == '(') 
					&& ptr[1] != '(') ) {
				err("WE DO GOTO BECAUSE WE CAN! (ptr == %c)\n", *ptr);
				if (ISNUM(ptr[1])) {
					goto ler_numero;
				} else {
					pfix.push_back(ptr++);
					ptr++;					
				}
				continue;
			}
			while (!ops.empty()) {
				char *top = ops.top();
				if (ISPAR(*top) || prec(*top) - prec(*ptr) < 0)
					break;
				desempilhar();
			}
			ops.push(ptr++);
			break;
		}
	}
	while (!ops.empty())
		desempilhar();


	stack<double> pilha;
	while (!pfix.empty()) {
		char *t = pfix.front();
		pfix.pop_front();
		err("Processing %c (t==buffer? %d)\n", *t, t==buffer);

		if (ISOP(*t) 
				&& t != buffer 
				&& !ISOP(t[-1]) && (t[-1] != '(')) {
			err("...\n");
			double b = pilha.top(); pilha.pop();
			double a = pilha.top(); pilha.pop();
			double r;
			switch(*t) {
			case '*': r = a * b; break;
			case '/': r = a / b; break;
			case '+': r = a + b; break;
			case '-': r = a - b; break;
			}
			err("eval %lf %c %lf = %lf\n", a, *t, b, r);
			pilha.push(r);
			continue;
		}
		if (ISOP(*t) && ISVAR(*(t+1))) {
			double v = MEMORY( *(t+1) );
			if (*t == '-') 
				v *= -1;
			err("With signal: %c%c (%lf)\n", t[0], t[1], v);
			pilha.push( v );
			continue;
		}
		if (ISVAR(*t)) {
			double v = MEMORY(*t);
			err("Push variable: %c (%lf)\n", *t, v);
			pilha.push( v );
		} else {
			double v = (double) strtol(t, NULL, 10);
			err("Push number: %c (%lf)\n", *t, v);
			pilha.push( v );
		}
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

