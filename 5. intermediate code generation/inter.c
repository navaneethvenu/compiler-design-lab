// 5. Intermediate Code Generator
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX];
char* ip = input;

int main() {
	printf("Enter input string:\n");
	scanf("%s", ip);
	// post fix expression and its pointer
	char post[MAX];
	char* p = post;
	// stack and top
	char stack[MAX];
	int top = -1;
	char ch = 'p';
	if(input[1] == '=') {
		ip += 2;
	}
	printf("\nIntermediate Code:\n");
	while(*ip != '\0') {
		if ((*ip >= 'a' && *ip <= 'z') || (*ip >= 'A' && *ip <= 'Z')) {
			*(p++) = *ip;
		} else if(*ip == '(') {
			stack[++top] = *ip;
		} else if(*ip == ')') {
			while(stack[top] != '(') {
				*(p++) = stack[top--];
				printf("%c = %c%c%c\n", ch++, *(p-3), *(p-1), *(p-2));
				*(p-3) = ch - 1;
				p -= 2;
			}
			top--;
		}
		else if (*ip == '+' || *ip == '-') {
			if (stack[top] == '*' || stack[top] == '/') {
				*(p++) = stack[top--];
				printf("%c = %c%c%c\n", ch++, *(p-3), *(p-1), *(p-2));
		*(p-3) = ch - 1;
		p -= 2;
				stack[++top] = *ip;
			} else {
				stack[++top] = *ip;
			}
		} else {
			if (stack[top] == '*' || stack[top] == '/') {
				*(p++) = stack[top--];
		*(p-3) = ch - 1;
		p -= 2;
				stack[++top] = *ip;
			} else {
				stack[++top] = *ip;
			}
		}
		stack[top + 1] = '\0';
		ip++;
	}
	while(top >= 0) {
		*(p++) = stack[top--];
		printf("%c = %c%c%c\n", ch++, *(p-3), *(p-1), *(p-2));
		*(p-3) = ch - 1;
		p -= 2;
	}
	if(input[1] == '=') {
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
