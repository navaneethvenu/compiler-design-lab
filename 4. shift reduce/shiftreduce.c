// 4. Shift reduce parser
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

//grammar
struct {
	char lhs;
	char rhs[MAX];
} prod[MAX];

int prodCount = 0;

// input string
char input[MAX];
// input pointer
char* ip = input;
// stack
char stack[MAX];
int top = -1;

bool shift();
bool reduce(int);

int main() {
	FILE *fp = fopen("grammar2.txt", "r");
	char line[MAX];
	printf("Grammar:\n");
	while(fscanf(fp, "%s", line) != EOF) {
		printf("%s\n", line);
		strcpy(prod[prodCount].rhs, line + 3);
		prod[prodCount].lhs = line[0];
		prodCount++;
	}
	printf("\nEnter input:\n");
	scanf("%s", input);
	// insert $ to right end of input string and stack
	strcat(input, "$");
	stack[++top] = '$';
	printf("\nStack\t\tInput\t\tAction\n");
	while(1) {
		for(int i = 0; i <= top; i++)
			printf("%c", stack[i]);
		printf("\t\t%s\t\t", ip);
		if(*ip == '$' && top == 1 && stack[top] == prod[0].lhs) {
			printf("Accept\n");
			return 0;
		}
		bool reduced = false;
		for (int i = 0; i < prodCount; i++) {
			if(reduce(i)) {
				printf("Reduce by %c->%s\n", prod[i].lhs, prod[i].rhs);
				reduced = true;
				break;
			}
		}
		bool shifted = false;
		if(!reduced) {
			shifted = shift();
			printf("Shift\n");
		}
		if(!shifted && !reduced) {
			printf("\nError in parsing\n");
			return 1;
		}
	}
	return 0;
}

bool shift() {
	// check if end of string reached
	if(*ip == '$')
		return false;
	stack[++top] = *(ip++);
	return true;
}

bool reduce(int prodNum) {
	// check for handle
	int bufferLength = strlen(prod[prodNum].rhs);
	if(bufferLength > top + 1)
		return false;
	char temp[MAX];
	for (int i = 0; i < bufferLength; i++) {
		temp[i] = stack[top + 1 - bufferLength + i];
	}
	temp[bufferLength] = '\0';
	if(strcmp(temp, prod[prodNum].rhs) != 0) {
		return false;
	}
	// reduce (replace handle with lhs of production)
	top-=bufferLength;
	for (int i = bufferLength; i > 0; i--) {
		//stack[++top] = prod[prodNum].rhs[i];
	}
	stack[++top] = prod[prodNum].lhs;
	return true;
}

/*
OUTPUT

Grammar:
E->E+E
E->E*E
E->(E)
E->i

Enter input:
i+i*i

Stack		Input		Action
$		i+i*i$		Shift
$i		+i*i$		Reduce by E->i
$E		+i*i$		Shift
$E+		i*i$		Shift
$E+i		*i$		Reduce by E->i
$E+E		*i$		Reduce by E->E+E
$E		*i$		Shift
$E*		i$		Shift
$E*i		$		Reduce by E->i
$E*E		$		Reduce by E->E*E
$E		$		Accept
*/
