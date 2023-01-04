// 2. Recursive descent parser
// Navaneeth Venu, Roll No. 44, S7 CS2

#include <stdio.h>
#define MAX 1000

char s[MAX];
char *p = s;

int E();
int T();
int F();

int main()
{
	printf("Enter a string:\n");
	scanf("%s", s);
	if (E() & *p == '\0')
		printf("Successfully parsed\n");
	else
		printf("Error in parsing\n");
	return 0;
}

// int E()
// {
// 	if (*p == '+')
// 	{
// 		p++;
// 		if (T())
// 		{
// 			if (F())
// 			{
// 				printf("E -> +TF\n");
// 				return 1;
// 			}
// 		}
// 	}
// 	return 0;
// }

// int T()
// {
// 	if (*p == 'a')
// 	{
// 		p++;
// 		if (*p == 'b')
// 		{
// 			printf("T -> ab\n");
// 			p++;
// 			return 1;
// 		}
// 		printf("T -> a\n");
// 		return 1;
// 	}
// 	return 0;
// }

// int F()
// {
// 	if (T())
// 	{
// 		if (*p == 'a')
// 		{
// 			p++;
// 			if (F())
// 			{
// 				printf("F -> TaF\n");
// 				return 1;
// 			}
// 		}
// 		return 0;
// 	}
// 	printf("F -> $\n");
// 	return 1;
// }

int E()
{
	if (*p == '+')
	{
		p++;
		if (T())
		{
			if (F())
			{
				printf("E->+TF\n");
				return 1;
			}
		}
	}
	return 0;
}

int F()
{
	if (T())
	{
		if (*p == 'a')
		{
			p++;
			if (F())
			{
				printf("E->TaF\n");
				return 1;
			}
		}
	}
	printf("E->$\n");
	return 1;
}

int T()
{
	if (*p == 'a')
	{
		p++;
		if (*p == 'b')
		{
			p++;
			printf("T->ab\n");
			return 1;
		}
		printf("T->a\n");
		return 1;
	}
	return 0;
}

/*
OUTPUT 1:
Enter a string:
+ababa
T -> ab
T -> ab
F -> $
F -> TaF
E -> +TF
Successfully parsed

OUTPUT 2:
Enter a string:
+ab
T -> ab
F -> $
E -> +TF
Successfully parsed

OUTPUT 3:
Enter a string:
+ba
Error in parsing
*/
