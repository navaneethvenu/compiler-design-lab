#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXINPUT 1000
#define MAX 100

char input[MAXINPUT];
int i = -1;

bool isDelimiter(char);
void checkId();
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
	// printf("processing %c\n", input[i + 1]);
	switch (input[++i])
	{
	case 'i':
		switch (input[++i])
		{
		case 'f':
			if (isValidDelimiter(input[i + 1]))
			{
				printf("Valid keyword: if\n");
				return;
			}
			else
				checkId();
		case 'n':
			if (input[++i] == 't' && isValidDelimiter(input[i + 1]))
			{
				printf("Valid keyword: int\n");
				return;
			}
			else
				checkId();
		default:
			checkId();
		}
		break;
	case 'm':
		if (input[++i] == 'a' && input[++i] == 'i' && input[++i] == 'n' && isValidDelimiter(input[i + 1]))
		{
			printf("Valid keyword: main\n");
			return;
		}
		else
			checkId();
		break;
	case '(':
	case ')':
	case '{':
	case '}':
	case ';':
		printf("Valid punctuator: %c\n", input[i]);
		return;
	case ' ':
	case '\n':
	case '\t':
		break;
	default:
		checkId();
	}
}

void checkId()
{
	printf("Identifier: %c\n", input[i]);
}

bool isValidDelimiter(char ch)
{
	return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
			ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
			ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
			ch == '[' || ch == ']' || ch == '{' || ch == '}');
}