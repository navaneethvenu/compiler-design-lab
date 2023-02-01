// 1. Lexical analyser
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXINPUT 1000
#define MAX 100

char input[MAXINPUT];
int i = -1;

bool isDelimiter(char);
void checkId();
void checkNum();
bool isValidDelimiter(char);
void getToken();

int main()
{
	FILE *inputFile = fopen("input.txt", "r");
	fscanf(inputFile, "%[^EOF]s", input);
	int count = 0;
	while (i + 1 < strlen(input))
	{
		getToken();
	}
	return 0;
}

void getToken()
{
	int j, start = i + 1;
	switch (input[++i])
	{
	case 'i':
		switch (input[++i])
		{
		case 'f':
			if (isValidDelimiter(input[i + 1]))
				printf("Valid keyword: if\n");
			else
			{
				i--;
				checkId();
			}
			return;
		case 'n':
			if (input[++i] == 't' && isValidDelimiter(input[i + 1]))
				printf("Valid keyword: int\n");
			else
			{
				i -= 2;
				checkId();
			}
			return;
		default:
			i--;
			checkId();
		}
		break;
	case 'm':
		if (input[++i] == 'a' && input[++i] == 'i' && input[++i] == 'n' && isValidDelimiter(input[i + 1]))
			printf("Valid keyword: main\n");
		else
		{
			i -= 2;
			checkId();
		}
		return;
	case 'v':
		if (input[++i] == 'o' && input[++i] == 'i' && input[++i] == 'd' && isValidDelimiter(input[i + 1]))
			printf("Valid keyword: void\n");
		else
		{
			i -= 3;
			checkId();
		}
		return;
	case 'f':
		if (input[++i] == 'o' && input[++i] == 'r' && isValidDelimiter(input[i + 1]))
			printf("Valid keyword: for\n");
		else
		{
			i -= 2;
			checkId();
		}
		return;
	case 'w':
		if (input[++i] == 'h' && input[++i] == 'i' && input[++i] == 'l' && input[++i] == 'e' && isValidDelimiter(input[i + 1]))
			printf("Valid keyword: while\n");
		else
		{
			i -= 4;
			checkId();
		}
		return;
	case '(':
	case ')':
	case '{':
	case '}':
	case ';':
		printf("Valid punctuator: %c\n", input[i]);
		return;
	case '*':
	case '/':
	case '=':
	case '>':
	case '<':
		printf("Valid operator: %c\n", input[i]);
		return;
	case '+':
		if (input[i + 1] == '+')
		{
			printf("Valid operator: ++\n");
			i++;
		}
		else
			printf("Valid operator: +\n");
		return;
	case '-':
		if (input[i + 1] == '-')
		{
			printf("Valid operator: --\n");
			i++;
		}
		else
			printf("Valid operator: -\n");
		return;
	case ' ':
	case '\n':
	case '\t':
		return;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		checkNum();
		return;
	default:
		checkId();
	}
}

void checkId()
{
	char id[MAX];
	int index = 0;
	while (!isValidDelimiter(input[i]))
	{
		id[index++] = input[i++];
	}
	id[index] = '\0';
	if (input[i] == '(')
	{
		printf("Function: %s\n", id);
		return;
	}
	i--;
	printf("Valid identifier: %s\n", id);
}

void checkNum()
{
	char id[MAX];
	int index = 0;
	bool invalid = false;
	while (!isValidDelimiter(input[i]))
	{
		if (!(input[i] == '0' || input[i] == '1' || input[i] == '2' || input[i] == '3' || input[i] == '4' || input[i] == '5' || input[i] == '6' || input[i] == '7' || input[i] == '8' || input[i] == '9'))
		{
			invalid = true;
		}
		id[index++] = input[i++];
	}
	i--;
	id[index] = '\0';
	if (invalid)
		printf("Invalid identifier: %s\n", id);
	else
		printf("Valid constant: %s\n", id);
}

bool isValidDelimiter(char ch)
{
	return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
			ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
			ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
			ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

/*
input.txt:
void main() {
	int 1ab = intb + c++ + 22;
	while(c)
	{
		ab++;
	}
}

OUTPUT:
Valid keyword: void
Valid keyword: main
Valid punctuator: (
Valid punctuator: )
Valid punctuator: {
Valid keyword: int
Invalid identifier: 1ab
Valid operator: =
Valid identifier: intb
Valid operator: +
Valid identifier: c
Valid operator: ++
Valid operator: +
Valid constant: 22
Valid punctuator: ;
Valid keyword: while
Valid punctuator: (
Valid identifier: c
Valid punctuator: )
Valid punctuator: {
Valid identifier: ab
Valid operator: ++
Valid punctuator: ;
Valid punctuator: }
Valid punctuator: }
*/
