#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <stack>

using namespace std;
float memory[26];
#define MEMORY(chr)	memory[chr - 'a']
#define ISNUM(chr)	'0' <= (chr) && (chr) <= '9'
#define ISVAR(chr)	'a' <= (chr) && (chr) <= 'z'
#define ISPAR(chr)	((chr) == '(' || (chr) == ')')
#define ISOP(c)		((c) == '*' || (c) == '/' || (c) == '+' || (c) == '-')
char buffer[301];

int prec(int op)
{
	switch (op) {
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	}
	return -100;
}

enum {VARIAVEL, NUMERO, OPERADOR, PARENTESE};
int token(int value)
{
	if (ISNUM(value))
		return NUMERO;
	if (ISVAR(value))
		return VARIAVEL;
	if (ISPAR(value))
		return PARENTESE;
	return OPERADOR;
}

stack<char *> ops;
list<char *> pfix;

void desempilhar(void)
{
	char *top = ops.top();
	ops.pop();
	if (*top != '(')
		pfix.push_back(top);
}

float eval(char *ptr)
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
			if (*ptr == '(')
				ops.push(ptr);
			else 
				while (*ops.top() != '(')
					desempilhar();
			ptr++;
			break;
		case OPERADOR:
			while (!ops.empty()) {
				char *top = ops.top();
				if (ISPAR(*top) || prec(*ptr) - prec(*top) <= 0)
					break;
				desempilhar();
			}
			ops.push(ptr++);
		}
	}
	while (!ops.empty())
		desempilhar();

	cout << "Posfixo: ";
	for (list<char *>::iterator i=pfix.begin(); i!=pfix.end(); i++)
		cout << *(*i);
	cout << endl << endl;

	stack<float> pilha;
	while (!pfix.empty()) {
		char *t = pfix.front();
		pfix.pop_front();

		if (ISOP(*t)) {
			float b = pilha.top(); pilha.pop();
			float a = pilha.top(); pilha.pop();
			float r;
			cout << "Eval " << a << " " << *t << " " << b << endl;
			switch(*t) {
			case '*': r = a * b; break;
			case '/': r = a / b; break;
			case '+': r = a + b; break;
			case '-': r = a - b; break;
			}
			pilha.push(r);
			continue;
		}
		if (ISVAR(*t)) {
			pilha.push( (float) MEMORY(*t) );
			continue;
		}
		if (ISNUM(*t)) {
			pilha.push( (float) strtol(t, NULL, 10) );
			continue;
		}

	}
	cout << "Result: " << pilha.top() << endl;
	return pilha.top();
}

void save_value(void)
{
	cout << "Saving in " << buffer[0] << " (" << string(buffer) << ")" << endl;
	MEMORY(*buffer) = eval(buffer + 2);
}

int main(void)
{
	memset(memory, 0, sizeof(memory));
	while (scanf("%s", buffer) == 1) {
		if (buffer[1] == '=')
			save_value();
		else
			printf("%.2f\n", eval(buffer));
	}
	return 0;
}

