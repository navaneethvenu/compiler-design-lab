%{
#include <stdio.h>
int c_letters = 0, s_letters = 0;
%}
%%
[A-Z] c_letters++;
[a-z] s_letters++;
%%
int main() {
	yyin = fopen("abc.txt", "r");
	yylex();
	printf("This file contains...\n");
	printf("%d capital letters\n", c_letters);
	printf("%d small letters\n", s_letters);
}

int yywrap() {
	return 1;
}
