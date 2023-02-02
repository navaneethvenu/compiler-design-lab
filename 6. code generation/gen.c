// 6. Generation of 8086 assemby instruction from 3 address code
// Amal Joe R S, Roll No. 64, S7 CS2

#include <stdio.h>

#define MAX 100

char regs[MAX];
int regCount = 0;

int getReg(char);

int main()
{
	FILE *fp = fopen("input.txt", "r");
	for (int i = 0; i < MAX; i++)
	{
		regs[i] = '\0';
	}
	char line[MAX];
	while (fscanf(fp, "%s", line) != EOF)
	{
		// printf("\nLine: %s\n", line);
		int index = getReg(line[2]);
		// printf("\tIndex: %d", index);
		// printf("\tRegcount: %d\n\t", regCount);
		if (regs[index] != line[2])
		{
			// 1st operand not in register
			printf("MOV R%d, %c\n", index, line[2]);
			regCount++;
		}

		int index2 = getReg(line[4]);
		// printf("\tIndex2: %d", index);
		// printf("\tRegcount: %d\n\t", regCount);
		char op2[3];
		if (regs[index2] == line[4])
		{
			// 2nd operand in register
			sprintf(op2, "R%d", index2);
		}
		else
		{
			// 2nd +operand not in register
			sprintf(op2, "%c", line[4]);
		}

		// printf("regs: %s\n", regs);
		switch (line[3])
		{
		case '+':
			printf("ADD R%d, %s\n", index, op2);
			break;
		case '-':
			printf("SUB R%d, %s\n", index, op2);
			break;
		case '*':
			printf("MUL R%d, %s\n", index, op2);
			break;
		case '/':
			printf("DIV R%d, %s\n", index, op2);
			break;
		}

		regs[index] = line[0];
	}
	return 0;
}

int getReg(char ch)
{
	for (int i = 0; i < regCount; i++)
	{
		if (regs[i] == ch)
		{
			return i;
		}
	}
	return regCount;
}

/*
INPUT
p=b-c
q=e*d
a=q+p

OUTPUT
MOV R0, b
SUB R0, c
MOV R2, e
MUL R2, d
ADD R2, R0
*/
