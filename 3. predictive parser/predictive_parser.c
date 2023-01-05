#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

// production structure
struct
{
	char rhs[MAX]; // rhs of prod
	char lhs;	   // lhs of prod
} prod[MAX];

char ip[MAX];
char s[MAX];

// number of productions (starts at 0)
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
	char line[MAX]; // stores each line of file
	printf("Grammar:\n");
	while (fscanf(fp, "%s", line) != EOF)
	{
		printf("%s\n", line);
		prod[prodNum].lhs = line[0];
		strcpy(prod[prodNum].rhs, line + 3);
		prodNum++;
	}
	printf("\n");

	bool done[26]; // represents each alphabet
	for (int i = 0; i < 26; i++)
	{
		done[i] = false;
	}

	for (int i = 0; i < prodNum; i++)
	{
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
	printf("\n");
	strcat(ip, "$");

	// predictive parser
	char stack[MAX];
	int top = -1;
	int ipPointer = 0;
	stack[++top] = prod[0].lhs;
	while (top >= 0 && ipPointer < strlen(ip))
	{

		char cStack = stack[top--];
		char cInput = ip[ipPointer];
		if (cStack == cInput)
		{
			ipPointer++;
			continue;
		}
		if (cStack > 'A' && cStack < 'Z')
		{
			bool found = false;

			for (int i = 0; i < prodNum; i++)
			{
				if (prod[i].lhs != cStack)
				{
					continue;
				}
				if (prod[i].rhs[0] > 'A' && prod[i].rhs[0] < 'Z')
				{

					char *first = getFirst(prod[i].rhs[0]);
					for (int j = 0; j < strlen(first); j++)
					{
						if (first[j] == cInput)
						{
							found = true;
							for (int k = strlen(prod[i].rhs) - 1; k >= 0; k--)
							{
								stack[++top] = prod[i].rhs[k];
							}
							printf("%c->%s\n", prod[i].lhs, prod[i].rhs);
							break;
						}
					}
					if (found)
						break;
					if (strchr(first, '#') != NULL)
					{
						char *follow = getFollow(prod[i].rhs[0]);
						for (int j = 0; j < strlen(follow); j++)
						{
							if (follow[j] == cInput)
							{
								found = true;
								for (int k = strlen(prod[i].rhs) - 1; k >= 0; k--)
								{
									stack[++top] = prod[i].rhs[k];
								}
								printf("%c->%s\n", prod[i].lhs, prod[i].rhs);
								break;
							}
						}
					}
					if (found)
						break;
					printf("\nError parsing string.\n");
					return 1;
				}
				else
				{
					if (prod[i].rhs[0] == cInput)
					{
						for (int k = strlen(prod[i].rhs) - 1; k >= 0; k--)
						{
							stack[++top] = prod[i].rhs[k];
						}
						printf("%c->%s\n", prod[i].lhs, prod[i].rhs);
						break;
					}
				}
				if (!found && prod[i].rhs[0] == '#')
				{
					printf("%c->%s\n", prod[i].lhs, prod[i].rhs);
				}
			}
		}
		else
		{
			printf("\nError parsing string.\n");
			return 1;
		}
	}
	while (top >= 0)
	{
		char cStack = stack[top];
		bool found = false;
		for (int i = 0; i < prodNum; i++)
		{
			if (cStack == prod[i].lhs && prod[i].rhs[0] == '#')
			{
				top--;
				found = true;
				break;
			}
		}
		if (!found)
			break;
	}
	if (top != -1 || ip[ipPointer] != '$')
	{
		printf("\nError parsing string.\n");
		return 1;
	}
	else
	{
		printf("\nString parsed successfully.\n");
	}
	return 0;
}

char *getFirst(char ch)
{
	tokenNum = 0;
	first(ch);
	s[tokenNum] = '\0'; // close s

	// removing duplicates
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

	// remove duplicates
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
			// This condition checks if the first character of the RHS of the prod is a capital letter.
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

				// check for capital letters (non terminals)
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
