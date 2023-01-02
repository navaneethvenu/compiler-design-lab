// 9. Calculator using LEX and YACC
// Amal Joe R S, Roll No. 64, S7 CS2

// cal.y

%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%token NUMBER ID

%%
// grammar production rule

expr: T {
	printf("Result=%d\n", $$);
	return 0;
}
T: 	T'+'T {$$ = $1 + $3;}
	|T'-'T {$$ = $1 - $3;}
	|T'*'T {$$ = $1 * $3;}
	|T'/'T {$$ = $1 / $3;}
	|'-'NUMBER {$$ = -$2;}
	|'-'ID {$$ = -$2;}
	|'('T')' {$$ = $2;}
	|NUMBER {$$ = $1;}
	|ID {$$ = $1;};
%%
int main() {
	printf("Enter the expression\n");
	yyparse();
}

/* for printing error messages */
int yyerror(char *s) {
	printf("\nExpression is invalid\n");
	exit(0);
}

/*
OUTPUT
Enter the expression
3+4*2
Result=11

OUTPUT 2
Enter the expression
3+4*2
Result=11
*/
