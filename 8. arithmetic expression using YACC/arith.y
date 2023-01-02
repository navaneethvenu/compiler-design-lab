// 8. YACC specification to recognise a valid arithmetic expression
// Amal Joe R S, Roll No. 64, S7 CS2

// arith.y

%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%token NUMBER ID

%%
// grammar production rule

expr:expr'+'expr
	|expr'-'expr
	|expr'*'expr
	|expr'/'expr
	|'-'NUMBER
	|'-'ID
	|'('expr')'
	|NUMBER
	|ID;
%%
int main() {
	printf("Enter the expression\n");
	yyparse();
	printf("\nExpression is valid\n");
}

/* for printing error messages */
int yyerror(char *s) {
	printf("\nExpression is invalid\n");
	exit(0);
}

/*
OUTPUT 1
Enter the expression
a+b*c

Expression is valid

OUTPUT 2
Enter the expression
a+(b*c

Expression is invalid
*/
