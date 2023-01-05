// 5. Intermediate Code Generator
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX];
char *ip = input;

int main()
{
	printf("Enter input string:\n");
	scanf("%s", ip);

	// post fix expression and its pointer
	char post[MAX];
	char *p = post;

	// stack and top
	char stack[MAX];
	int top = -1;

	// start of temp variables
	char ch = 'p';

	// skip to expr for statements of type e=expr
	if (input[1] == '=')
	{
		ip += 2;
	}

	printf("\nIntermediate Code:\n");

	// until end of ip
	while (*ip != '\0')
	{
		// if letter, add to postfix
		if ((*ip >= 'a' && *ip <= 'z') || (*ip >= 'A' && *ip <= 'Z'))
		{
			*(p++) = *ip;
		}

		// if opening bracket, add to stack
		else if (*ip == '(')
		{
			stack[++top] = *ip;
		}

		// if closing bracket, pop stack until opening is found
		else if (*ip == ')')
		{
			while (stack[top] != '(')
			{
				*(p++) = stack[top--]; // popping and adding to postfix

				printf("%c = %c%c%c\n", ch++, *(p - 3), *(p - 1), *(p - 2));

				// replace with temp variable
				*(p - 3) = ch - 1;
				p -= 2;
			}
			top--;
		}

		// if operator + and -
		else if (*ip == '+' || *ip == '-')
		{
			// current are higher precedence -> pop
			if (stack[top] == '*' || stack[top] == '/')
			{
				// pop to postfix
				*(p++) = stack[top--];
				printf("%c = %c%c%c\n", ch++, *(p - 3), *(p - 1), *(p - 2));

				*(p - 3) = ch - 1;
				p -= 2;

				// append new to stack
				stack[++top] = *ip;
			}
			else
			{
				stack[++top] = *ip;
			}
		}
		else
		{
			// if current * and / (higher precedence)
			if (stack[top] == '*' || stack[top] == '/')
			{
				*(p++) = stack[top--];
				*(p - 3) = ch - 1;
				p -= 2;
				stack[++top] = *ip;
			}
			else
			{
				stack[++top] = *ip;
			}
		}
		stack[top + 1] = '\0';
		ip++;
	}
	while (top >= 0)
	{
		*(p++) = stack[top--];
		printf("%c = %c%c%c\n", ch++, *(p - 3), *(p - 1), *(p - 2));
		*(p - 3) = ch - 1;
		p -= 2;
	}
	if (input[1] == '=')
	{
		printf("%c = %c\n", input[0], post[0]);
	}
	return 0;
}

/*
OUTPUT
Enter input string:
e=a+(b+c*d)

Intermediate Code:
p = c*d
q = b+p
r = a+q
e = r
*/
