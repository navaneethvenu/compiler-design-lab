#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

struct
{
	char rhs[MAX];
	char lhs;
} prod[MAX];

char ip[MAX];
char s[MAX];
int prodNum = 0;
int tokenNum = 0;
int table[MAX][MAX];

char *getToken();
char *getFirst(char);
char *getFollow(char);
char *first(char);
char *follow(char);

int main()
{
	FILE *fp = fopen("grammar.txt", "r");
	char line[MAX];
	printf("Grammar:\n");
	while (fscanf(fp, "%s", line) != EOF)
	{
		printf("%s\n", line);
		prod[prodNum].lhs = line[0];
		strcpy(prod[prodNum].rhs, line + 3);
		prodNum++;
	}
	printf("\n");
	bool done[26];
	for (int i = 0; i < 26; i++)
	{
		done[i] = false;
	}
	for (int i = 0; i < prodNum; i++)
	{
		// printf("%c -> %s\n", prod[i].lhs, prod[i].rhs);
		if (done[prod[i].lhs - 65])
		{
			continue;
		}
		done[prod[i].lhs - 65] = true;
		char *temp = getFirst(prod[i].lhs);
		printf("first of %c = %s\n", prod[i].lhs, temp);
	}
	for (int i = 0; i < 26; i++)
	{
		done[i] = false;
	}
	for (int i = 0; i < prodNum; i++)
	{
		// printf("%c -> %s\n", prod[i].lhs, prod[i].rhs);
		if (done[prod[i].lhs - 65])
		{
			continue;
		}
		done[prod[i].lhs - 65] = true;
		char *temp = getFollow(prod[i].lhs);
		printf("follow of %c = %s\n", prod[i].lhs, temp);
	}
	printf("\nEnter input string:\n");
	scanf("%s", ip);
	strcat(s, "$");
	// predictive parser
	char stack[MAX];
	int top = -1;
	int ipPointer = 0;
	stack[++top] = prod[0].lhs;
	while(top >= 0 && ipPointer < strlen(ip)) {
		char cStack = stack[top--];
		char cInput = ip[ipPointer++];
		if(cStack == cInput) {
			continue;
		}
		if(cStack > 'A' && cStack < 'Z') {
			
		}
	}
	return 0;
}

char *getFirst(char ch)
{
	tokenNum = 0;
	first(ch);
	s[tokenNum] = '\0';
	for (int i = 0; i < strlen(s); i++)
	{
		for (int j = i + 1; j < strlen(s); j++)
		{
			if (s[i] == s[j])
			{
				s[j] = ' ';
			}
		}
	}
	for (int i = 0; i < tokenNum; i++)
	{
		if (s[i] != ' ')
		{
			continue;
		}
		tokenNum--;
		for (int j = i; j < tokenNum; j++)
		{
			s[j] = s[j + 1];
		}
	}
	return s;
}

char *getFollow(char ch)
{
	tokenNum = 0;
	follow(ch);
	s[tokenNum] = '\0';
	for (int i = 0; i < strlen(s); i++)
	{
		for (int j = i + 1; j < strlen(s); j++)
		{
			if (s[i] == s[j])
			{
				s[j] = ' ';
			}
		}
	}
	for (int i = 0; i < tokenNum; i++)
	{
		if (s[i] != ' ')
		{
			continue;
		}
		tokenNum--;
		for (int j = i; j < tokenNum; j++)
		{
			s[j] = s[j + 1];
		}
	}
	return s;
}

char *first(char ch)
{
	for (int i = 0; i < prodNum; i++)
	{
		if (prod[i].lhs == ch)
		{
			if (prod[i].rhs[0] >= 'A' && prod[i].rhs[0] <= 'Z')
			{
				first(prod[i].rhs[0]);
				break;
			}
			s[tokenNum++] = prod[i].rhs[0];
		}
	}
	return s;
}

char *follow(char ch)
{
	// starting production
	if (ch == prod[0].lhs)
	{
		s[tokenNum++] = '$';
	}
	for (int i = 0; i < prodNum; i++)
	{
		for (int j = 0; j < strlen(prod[i].rhs); j++)
		{
			if (prod[i].rhs[j] == ch)
			{
				if (prod[i].rhs[j + 1] == '\0')
				{
					if (prod[i].rhs[j] != prod[i].lhs)
						follow(prod[i].lhs);
				}
				else if (prod[i].rhs[j + 1] >= 'A' && prod[i].rhs[j + 1] <= 'Z')
				{
					first(prod[i].rhs[j + 1]);
					for (int k = 0; k < tokenNum; k++)
					{
						if (s[k] == '#')
						{
							s[k] = ' ';
							follow(prod[i].rhs[j + 1]);
						}
					}
				}
				else
				{
					s[tokenNum++] = prod[i].rhs[j + 1];
				}
			}
		}
	}
	return s;
}
