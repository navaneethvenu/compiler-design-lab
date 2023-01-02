%{
#include <stdio.h>
int sen = 0, blanks = 0, lines = 0, digits = 0, cLet = 0, sLet = 0;
%}
%%
[0-9] digits++;
[a-z] sLet++;
[A-Z] cLet++;
[ ] blanks++;
[\n] lines++;
[.] sen++;
%%
int main() {
	yyin = fopen("abc.txt", "r");
	yylex();
	printf("Sentences: %d\n", sen);
	printf("Words: %d\n", blanks + 1);
	printf("Lines: %d\n", lines);
	printf("Digits: %d\n", digits);
	printf("Capital letters: %d\n", cLet);
	printf("Small letters: %d\n", sLet);
}

int yywrap() {
	return 1;
}
